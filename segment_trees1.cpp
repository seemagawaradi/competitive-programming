#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct segtree
{
    ll size;
    vector<ll> sums;
    void init(ll n)
    {
        size = 1;
        while (size < n)
            size *= 2;
        sums.assign(2 * size, 0);
    }
    void set(ll i, ll v, ll x, ll lx, ll rx)
    {
        if (rx - lx == 1)
        {
            sums[x] = v;
            return;
        }
        ll m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, v, 2 * x + 1, lx, m);
        }
        else
        {
            set(i, v, 2 * x + 2, m, rx);
        }
        sums[x] = sums[2 * x + 1] + sums[2 * x + 2];
    }

    void set(ll i, ll v)
    {
        set(i, v, 0, 0, size);
    }

    ll sum(ll l, ll r, ll x, ll lx, ll rx)
    {
        if (l >= rx || r <= lx)
            return 0;
        if (lx >= l && rx <= r)
            return sums[x];
        ll m = (lx + rx) / 2;
        ll s1 = sum(l, r, 2 * x + 1, lx, m);
        ll s2 = sum(l, r, 2 * x + 2, m, rx);
        return s1 + s2;
    }
    ll sum(ll l, ll r)
    {
        return sum(l, r, 0, 0, size);
    }
};

int main()
{

    ll n, m; //size of array and number of operations
    cin >> n >> m;
    segtree st;
    st.init(n);
    for (ll i = 0; i < n; i++)
    {
        ll v;
        cin >> v;
        st.set(i, v);
    }
    while (m--)
    {
        ll op;
        cin >> op;
        if (op == 1)
        {
            ll i, v;
            cin >> i >> v;
            st.set(i, v);
        }
        else
        {
            ll l, r;
            cin >> l >> r;
            cout << st.sum(l, r) << "\n";
        }
    }
}
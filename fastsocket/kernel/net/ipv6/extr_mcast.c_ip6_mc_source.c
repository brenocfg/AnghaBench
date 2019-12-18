#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipv6_pinfo {struct ipv6_mc_socklist* ipv6_mc_list; } ;
struct ipv6_mc_socklist {int sfmode; int /*<<< orphan*/  sflock; struct ip6_sf_socklist* sflist; int /*<<< orphan*/  addr; int /*<<< orphan*/  ifindex; struct ipv6_mc_socklist* next; } ;
struct ip6_sf_socklist {int sl_count; int sl_max; struct in6_addr* sl_addr; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct net_device* dev; } ;
struct group_source_req {int /*<<< orphan*/  gsr_interface; int /*<<< orphan*/  gsr_group; int /*<<< orphan*/  gsr_source; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IP6_SFBLOCK ; 
 int /*<<< orphan*/  IP6_SFLSIZE (int) ; 
 int MCAST_INCLUDE ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_mc_add_src (struct inet6_dev*,struct in6_addr*,int,int,struct in6_addr*,int) ; 
 int /*<<< orphan*/  ip6_mc_del_src (struct inet6_dev*,struct in6_addr*,int,int,struct in6_addr*,int) ; 
 struct inet6_dev* ip6_mc_find_dev (struct net*,struct in6_addr*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv6_addr_equal (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_addr_is_multicast (struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_sk_mc_lock ; 
 int ipv6_sock_mc_drop (struct sock*,int /*<<< orphan*/ ,struct in6_addr*) ; 
 int memcmp (struct in6_addr*,struct in6_addr*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ip6_sf_socklist*,int /*<<< orphan*/ ) ; 
 struct ip6_sf_socklist* sock_kmalloc (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int sysctl_mld_max_msf ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int ip6_mc_source(int add, int omode, struct sock *sk,
	struct group_source_req *pgsr)
{
	struct in6_addr *source, *group;
	struct ipv6_mc_socklist *pmc;
	struct net_device *dev;
	struct inet6_dev *idev;
	struct ipv6_pinfo *inet6 = inet6_sk(sk);
	struct ip6_sf_socklist *psl;
	struct net *net = sock_net(sk);
	int i, j, rv;
	int leavegroup = 0;
	int pmclocked = 0;
	int err;

	source = &((struct sockaddr_in6 *)&pgsr->gsr_source)->sin6_addr;
	group = &((struct sockaddr_in6 *)&pgsr->gsr_group)->sin6_addr;

	if (!ipv6_addr_is_multicast(group))
		return -EINVAL;

	idev = ip6_mc_find_dev(net, group, pgsr->gsr_interface);
	if (!idev)
		return -ENODEV;
	dev = idev->dev;

	err = -EADDRNOTAVAIL;

	read_lock_bh(&ipv6_sk_mc_lock);
	for (pmc=inet6->ipv6_mc_list; pmc; pmc=pmc->next) {
		if (pgsr->gsr_interface && pmc->ifindex != pgsr->gsr_interface)
			continue;
		if (ipv6_addr_equal(&pmc->addr, group))
			break;
	}
	if (!pmc) {		/* must have a prior join */
		err = -EINVAL;
		goto done;
	}
	/* if a source filter was set, must be the same mode as before */
	if (pmc->sflist) {
		if (pmc->sfmode != omode) {
			err = -EINVAL;
			goto done;
		}
	} else if (pmc->sfmode != omode) {
		/* allow mode switches for empty-set filters */
		ip6_mc_add_src(idev, group, omode, 0, NULL, 0);
		ip6_mc_del_src(idev, group, pmc->sfmode, 0, NULL, 0);
		pmc->sfmode = omode;
	}

	write_lock_bh(&pmc->sflock);
	pmclocked = 1;

	psl = pmc->sflist;
	if (!add) {
		if (!psl)
			goto done;	/* err = -EADDRNOTAVAIL */
		rv = !0;
		for (i=0; i<psl->sl_count; i++) {
			rv = memcmp(&psl->sl_addr[i], source,
				sizeof(struct in6_addr));
			if (rv == 0)
				break;
		}
		if (rv)		/* source not found */
			goto done;	/* err = -EADDRNOTAVAIL */

		/* special case - (INCLUDE, empty) == LEAVE_GROUP */
		if (psl->sl_count == 1 && omode == MCAST_INCLUDE) {
			leavegroup = 1;
			goto done;
		}

		/* update the interface filter */
		ip6_mc_del_src(idev, group, omode, 1, source, 1);

		for (j=i+1; j<psl->sl_count; j++)
			psl->sl_addr[j-1] = psl->sl_addr[j];
		psl->sl_count--;
		err = 0;
		goto done;
	}
	/* else, add a new source to the filter */

	if (psl && psl->sl_count >= sysctl_mld_max_msf) {
		err = -ENOBUFS;
		goto done;
	}
	if (!psl || psl->sl_count == psl->sl_max) {
		struct ip6_sf_socklist *newpsl;
		int count = IP6_SFBLOCK;

		if (psl)
			count += psl->sl_max;
		newpsl = sock_kmalloc(sk, IP6_SFLSIZE(count), GFP_ATOMIC);
		if (!newpsl) {
			err = -ENOBUFS;
			goto done;
		}
		newpsl->sl_max = count;
		newpsl->sl_count = count - IP6_SFBLOCK;
		if (psl) {
			for (i=0; i<psl->sl_count; i++)
				newpsl->sl_addr[i] = psl->sl_addr[i];
			sock_kfree_s(sk, psl, IP6_SFLSIZE(psl->sl_max));
		}
		pmc->sflist = psl = newpsl;
	}
	rv = 1;	/* > 0 for insert logic below if sl_count is 0 */
	for (i=0; i<psl->sl_count; i++) {
		rv = memcmp(&psl->sl_addr[i], source, sizeof(struct in6_addr));
		if (rv == 0)
			break;
	}
	if (rv == 0)		/* address already there is an error */
		goto done;
	for (j=psl->sl_count-1; j>=i; j--)
		psl->sl_addr[j+1] = psl->sl_addr[j];
	psl->sl_addr[i] = *source;
	psl->sl_count++;
	err = 0;
	/* update the interface list */
	ip6_mc_add_src(idev, group, omode, 1, source, 1);
done:
	if (pmclocked)
		write_unlock_bh(&pmc->sflock);
	read_unlock_bh(&ipv6_sk_mc_lock);
	read_unlock_bh(&idev->lock);
	in6_dev_put(idev);
	dev_put(dev);
	if (leavegroup)
		return ipv6_sock_mc_drop(sk, pgsr->gsr_interface, group);
	return err;
}
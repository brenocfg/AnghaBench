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
struct sockaddr_pn {int /*<<< orphan*/  spn_family; } ;
struct sock {int dummy; } ;
struct pn_sock {int /*<<< orphan*/  sobject; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PHONET ; 
 int EADDRINUSE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_pn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phonet_get_local_port_range (int*,int*) ; 
 int /*<<< orphan*/  pn_addr (int /*<<< orphan*/ ) ; 
 struct sock* pn_find_sock_by_sa (struct net*,struct sockaddr_pn*) ; 
 int /*<<< orphan*/  pn_object (int /*<<< orphan*/ ,unsigned short) ; 
 struct pn_sock* pn_sk (struct sock*) ; 
 int /*<<< orphan*/  pn_sockaddr_set_port (struct sockaddr_pn*,unsigned short) ; 
 int /*<<< orphan*/  port_mutex ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

int pn_sock_get_port(struct sock *sk, unsigned short sport)
{
	static int port_cur;
	struct net *net = sock_net(sk);
	struct pn_sock *pn = pn_sk(sk);
	struct sockaddr_pn try_sa;
	struct sock *tmpsk;

	memset(&try_sa, 0, sizeof(struct sockaddr_pn));
	try_sa.spn_family = AF_PHONET;
	WARN_ON(!mutex_is_locked(&port_mutex));
	if (!sport) {
		/* search free port */
		int port, pmin, pmax;

		phonet_get_local_port_range(&pmin, &pmax);
		for (port = pmin; port <= pmax; port++) {
			port_cur++;
			if (port_cur < pmin || port_cur > pmax)
				port_cur = pmin;

			pn_sockaddr_set_port(&try_sa, port_cur);
			tmpsk = pn_find_sock_by_sa(net, &try_sa);
			if (tmpsk == NULL) {
				sport = port_cur;
				goto found;
			} else
				sock_put(tmpsk);
		}
	} else {
		/* try to find specific port */
		pn_sockaddr_set_port(&try_sa, sport);
		tmpsk = pn_find_sock_by_sa(net, &try_sa);
		if (tmpsk == NULL)
			/* No sock there! We can use that port... */
			goto found;
		else
			sock_put(tmpsk);
	}
	/* the port must be in use already */
	return -EADDRINUSE;

found:
	pn->sobject = pn_object(pn_addr(pn->sobject), sport);
	return 0;
}
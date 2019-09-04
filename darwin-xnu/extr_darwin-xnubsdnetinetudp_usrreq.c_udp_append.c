#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ip {int dummy; } ;
struct inpcb {int inp_flags; TYPE_3__* inp_socket; } ;
struct ifnet {int dummy; } ;
typedef  int boolean_t ;
struct TYPE_7__ {int so_options; int /*<<< orphan*/  so_rcv; } ;
struct TYPE_6__ {int /*<<< orphan*/  udps_fullsock; } ;

/* Variables and functions */
 int IFNET_IS_CELLULAR (struct ifnet*) ; 
 scalar_t__ IFNET_IS_WIFI (struct ifnet*) ; 
 scalar_t__ IFNET_IS_WIRED (struct ifnet*) ; 
 int /*<<< orphan*/  INP_ADD_STAT (struct inpcb*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int INP_CONTROLOPTS ; 
 int SO_TIMESTAMP ; 
 int SO_TIMESTAMP_CONTINUOUS ; 
 int SO_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  inp_set_activity_bitmap (struct inpcb*) ; 
 int ip_savecontrol (struct inpcb*,struct mbuf**,struct ip*,struct mbuf*) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ nstat_collect ; 
 int /*<<< orphan*/  rxbytes ; 
 int /*<<< orphan*/  rxpackets ; 
 scalar_t__ sbappendaddr (int /*<<< orphan*/ *,struct sockaddr*,struct mbuf*,struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  so_recv_data_stat (TYPE_3__*,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorwakeup (TYPE_3__*) ; 
 TYPE_2__ udpstat ; 

__attribute__((used)) static void
#if INET6
udp_append(struct inpcb *last, struct ip *ip, struct mbuf *n, int off,
    struct sockaddr_in *pudp_in, struct udp_in6 *pudp_in6,
    struct udp_ip6 *pudp_ip6, struct ifnet *ifp)
#else /* !INET6 */
udp_append(struct inpcb *last, struct ip *ip, struct mbuf *n, int off,
    struct sockaddr_in *pudp_in, struct ifnet *ifp)
#endif /* !INET6 */
{
	struct sockaddr *append_sa;
	struct mbuf *opts = 0;
	boolean_t cell = IFNET_IS_CELLULAR(ifp);
	boolean_t wifi = (!cell && IFNET_IS_WIFI(ifp));
	boolean_t wired = (!wifi && IFNET_IS_WIRED(ifp));
	int ret = 0;

#if CONFIG_MACF_NET
	if (mac_inpcb_check_deliver(last, n, AF_INET, SOCK_DGRAM) != 0) {
		m_freem(n);
		return;
	}
#endif /* CONFIG_MACF_NET */
	if ((last->inp_flags & INP_CONTROLOPTS) != 0 ||
	    (last->inp_socket->so_options & SO_TIMESTAMP) != 0 ||
	    (last->inp_socket->so_options & SO_TIMESTAMP_MONOTONIC) != 0 ||
		(last->inp_socket->so_options & SO_TIMESTAMP_CONTINUOUS) != 0) {
#if INET6
		if (last->inp_vflag & INP_IPV6) {
			int savedflags;

			if (pudp_ip6->uip6_init_done == 0) {
				ip_2_ip6_hdr(&pudp_ip6->uip6_ip6, ip);
				pudp_ip6->uip6_init_done = 1;
			}
			savedflags = last->inp_flags;
			last->inp_flags &= ~INP_UNMAPPABLEOPTS;
			ret = ip6_savecontrol(last, n, &opts);
			if (ret != 0) {
				last->inp_flags = savedflags;
				goto error;
			}
			last->inp_flags = savedflags;
		} else
#endif /* INET6 */
		{
			ret = ip_savecontrol(last, &opts, ip, n);
			if (ret != 0) {
				goto error;
			}
		}
	}
#if INET6
	if (last->inp_vflag & INP_IPV6) {
		if (pudp_in6->uin6_init_done == 0) {
			in6_sin_2_v4mapsin6(pudp_in, &pudp_in6->uin6_sin);
			pudp_in6->uin6_init_done = 1;
		}
		append_sa = (struct sockaddr *)&pudp_in6->uin6_sin;
	} else
#endif /* INET6 */
	append_sa = (struct sockaddr *)pudp_in;
	if (nstat_collect) {
		INP_ADD_STAT(last, cell, wifi, wired, rxpackets, 1);
		INP_ADD_STAT(last, cell, wifi, wired, rxbytes,
		    n->m_pkthdr.len);
		inp_set_activity_bitmap(last);
	}
	so_recv_data_stat(last->inp_socket, n, 0);
	m_adj(n, off);
	if (sbappendaddr(&last->inp_socket->so_rcv, append_sa,
	    n, opts, NULL) == 0) {
		udpstat.udps_fullsock++;
	} else {
		sorwakeup(last->inp_socket);
	}
	return;
error:
	m_freem(n);
	m_freem(opts);
}
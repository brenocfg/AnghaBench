#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int64_t ;
struct ifnet {TYPE_2__* if_udp_stat; TYPE_1__* if_tcp_stat; } ;
struct if_packet_stats {int /*<<< orphan*/  ifi_udp_badipsec; int /*<<< orphan*/  ifi_udp_cleanup; int /*<<< orphan*/  ifi_udp_badmcast; int /*<<< orphan*/  ifi_udp_badchksum; int /*<<< orphan*/  ifi_udp_badlength; int /*<<< orphan*/  ifi_udp_port0; int /*<<< orphan*/  ifi_udp_faithprefix; int /*<<< orphan*/  ifi_udp_port_unreach; int /*<<< orphan*/  ifi_tcp_synwindow; int /*<<< orphan*/  ifi_tcp_cleanup; int /*<<< orphan*/  ifi_tcp_dospacket; int /*<<< orphan*/  ifi_tcp_rstinsynrcv; int /*<<< orphan*/  ifi_tcp_ooopacket; int /*<<< orphan*/  ifi_tcp_deprecate6; int /*<<< orphan*/  ifi_tcp_icmp6unreach; int /*<<< orphan*/  ifi_tcp_listbadsyn; int /*<<< orphan*/  ifi_tcp_noconnlist; int /*<<< orphan*/  ifi_tcp_noconnnolist; int /*<<< orphan*/  ifi_tcp_badformatipsec; int /*<<< orphan*/  ifi_tcp_synfin; int /*<<< orphan*/  ifi_tcp_unspecv6; int /*<<< orphan*/  ifi_tcp_badformat; } ;
struct TYPE_4__ {int /*<<< orphan*/  badipsec; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  badmcast; int /*<<< orphan*/  badchksum; int /*<<< orphan*/  badlength; int /*<<< orphan*/  port0; int /*<<< orphan*/  faithprefix; int /*<<< orphan*/  port_unreach; } ;
struct TYPE_3__ {int /*<<< orphan*/  synwindow; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  dospacket; int /*<<< orphan*/  rstinsynrcv; int /*<<< orphan*/  ooopacket; int /*<<< orphan*/  deprecate6; int /*<<< orphan*/  icmp6unreach; int /*<<< orphan*/  listbadsyn; int /*<<< orphan*/  noconnlist; int /*<<< orphan*/  noconnnolist; int /*<<< orphan*/  badformatipsec; int /*<<< orphan*/  synfin; int /*<<< orphan*/  unspecv6; int /*<<< orphan*/  badformat; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_get_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
if_copy_packet_stats(struct ifnet *ifp, struct if_packet_stats *if_ps)
{
#define	COPY_IF_PS_TCP_FIELD64_ATOMIC(fld) do {				\
	atomic_get_64(if_ps->ifi_tcp_##fld,				\
	    (u_int64_t *)(void *)(uintptr_t)&ifp->if_tcp_stat->fld);	\
} while (0)

#define	COPY_IF_PS_UDP_FIELD64_ATOMIC(fld) do {				\
	atomic_get_64(if_ps->ifi_udp_##fld,				\
	    (u_int64_t *)(void *)(uintptr_t)&ifp->if_udp_stat->fld);	\
} while (0)

	COPY_IF_PS_TCP_FIELD64_ATOMIC(badformat);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(unspecv6);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(synfin);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(badformatipsec);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(noconnnolist);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(noconnlist);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(listbadsyn);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(icmp6unreach);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(deprecate6);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(ooopacket);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(rstinsynrcv);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(dospacket);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(cleanup);
	COPY_IF_PS_TCP_FIELD64_ATOMIC(synwindow);

	COPY_IF_PS_UDP_FIELD64_ATOMIC(port_unreach);
	COPY_IF_PS_UDP_FIELD64_ATOMIC(faithprefix);
	COPY_IF_PS_UDP_FIELD64_ATOMIC(port0);
	COPY_IF_PS_UDP_FIELD64_ATOMIC(badlength);
	COPY_IF_PS_UDP_FIELD64_ATOMIC(badchksum);
	COPY_IF_PS_UDP_FIELD64_ATOMIC(badmcast);
	COPY_IF_PS_UDP_FIELD64_ATOMIC(cleanup);
	COPY_IF_PS_UDP_FIELD64_ATOMIC(badipsec);

#undef COPY_IF_PS_TCP_FIELD64_ATOMIC
#undef COPY_IF_PS_UDP_FIELD64_ATOMIC
}
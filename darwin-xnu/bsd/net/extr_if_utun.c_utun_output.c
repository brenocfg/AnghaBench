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
typedef  int /*<<< orphan*/  u_int32_t ;
struct utun_pcb {scalar_t__ utun_ifp; int utun_flags; int /*<<< orphan*/  utun_ext_ifdata_stats; int /*<<< orphan*/  utun_use_netif; int /*<<< orphan*/  utun_unit; scalar_t__ utun_ctlref; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ ifnet_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DATA_EOR ; 
 int /*<<< orphan*/  DLT_NULL ; 
 int UTUN_FLAGS_NO_OUTPUT ; 
 scalar_t__ UTUN_HEADER_SIZE (struct utun_pcb*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bpf_tap_out (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ctl_enqueuembuf (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct utun_pcb* ifnet_softc (scalar_t__) ; 
 int /*<<< orphan*/  ifnet_stat_increment_out (scalar_t__,int,int,int) ; 
 scalar_t__ m_pktlen (int /*<<< orphan*/ ) ; 
 scalar_t__ mbuf_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int mbuf_pkthdr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 

__attribute__((used)) static errno_t
utun_output(ifnet_t	interface,
			mbuf_t data)
{
	struct utun_pcb	*pcb = ifnet_softc(interface);
	errno_t result;

	VERIFY(interface == pcb->utun_ifp);

#if UTUN_NEXUS
	if (!pcb->utun_use_netif)
#endif // UTUN_NEXUS
	{
		if (m_pktlen(data) >= (int32_t)UTUN_HEADER_SIZE(pcb)) {
			bpf_tap_out(pcb->utun_ifp, DLT_NULL, data, 0, 0);
		}
	}

	if (pcb->utun_flags & UTUN_FLAGS_NO_OUTPUT) {
		/* flush data */
		mbuf_freem(data);
		return 0;
	}

	// otherwise, fall thru to ctl_enqueumbuf
	if (pcb->utun_ctlref) {
		int	length;

		/*
		 * The ABI requires the protocol in network byte order
		 */
		if (m_pktlen(data) >= (int32_t)UTUN_HEADER_SIZE(pcb)) {
			*(u_int32_t *)mbuf_data(data) = htonl(*(u_int32_t *)mbuf_data(data));
		}

		length = mbuf_pkthdr_len(data);
		result = ctl_enqueuembuf(pcb->utun_ctlref, pcb->utun_unit, data, CTL_DATA_EOR);
		if (result != 0) {
			mbuf_freem(data);
			printf("utun_output - ctl_enqueuembuf failed: %d\n", result);
#if UTUN_NEXUS
			if (!pcb->utun_use_netif)
#endif // UTUN_NEXUS
			{
				ifnet_stat_increment_out(interface, 0, 0, 1);
			}
		} else {
#if UTUN_NEXUS
			if (!pcb->utun_use_netif)
#endif // UTUN_NEXUS
			{
				if (!pcb->utun_ext_ifdata_stats) {
					ifnet_stat_increment_out(interface, 1, length, 0);
				}
			}
		}
	} else {
		mbuf_freem(data);
	}
	
	return 0;
}
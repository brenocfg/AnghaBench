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
typedef  scalar_t__ u_int32_t ;
struct utun_pcb {scalar_t__ utun_max_pending_packets; int /*<<< orphan*/  utun_ifp; int /*<<< orphan*/  utun_unit; scalar_t__ utun_ctlref; int /*<<< orphan*/  utun_pcb_lock; int /*<<< orphan*/ * utun_kpipe_rxring; scalar_t__ utun_kpipe_enabled; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 scalar_t__ ctl_getenqueuepacketcount (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ ctl_getenqueuereadable (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ ifnet_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ifnet_disable_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lock_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lock_shared (int /*<<< orphan*/ ) ; 
 struct utun_pcb* ifnet_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_channel_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 scalar_t__ utun_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
utun_start(ifnet_t interface)
{
	mbuf_t data;
	struct utun_pcb *pcb = ifnet_softc(interface);

	VERIFY(pcb != NULL);

#if UTUN_NEXUS
	lck_rw_lock_shared(&pcb->utun_pcb_lock);
	if (pcb->utun_kpipe_enabled) {
		/* It's possible to have channels enabled, but not yet have the channel opened,
		 * in which case the rxring will not be set
		 */
		lck_rw_unlock_shared(&pcb->utun_pcb_lock);
		if (pcb->utun_kpipe_rxring != NULL) {
			kern_channel_notify(pcb->utun_kpipe_rxring, 0);
		}
		return;
	}
	lck_rw_unlock_shared(&pcb->utun_pcb_lock);
#endif // UTUN_NEXUS

	for (;;) {
		bool can_accept_packets = true;
		ifnet_lock_shared(pcb->utun_ifp);

		u_int32_t utun_packet_cnt;
		errno_t error_pc = ctl_getenqueuepacketcount(pcb->utun_ctlref, pcb->utun_unit, &utun_packet_cnt);
		if (error_pc != 0) {
			printf("utun_start: ctl_getenqueuepacketcount returned error %d\n", error_pc);
			utun_packet_cnt = 0;
		}

		can_accept_packets = (utun_packet_cnt < pcb->utun_max_pending_packets);
		if (!can_accept_packets && pcb->utun_ctlref) {
			u_int32_t difference = 0;
			if (ctl_getenqueuereadable(pcb->utun_ctlref, pcb->utun_unit, &difference) == 0) {
				if (difference > 0) {
					// If the low-water mark has not yet been reached, we still need to enqueue data
					// into the buffer
					can_accept_packets = true;
				}
			}
		}
		if (!can_accept_packets) {
			errno_t error = ifnet_disable_output(interface);
			if (error != 0) {
				printf("utun_start: ifnet_disable_output returned error %d\n", error);
			}
			ifnet_lock_done(pcb->utun_ifp);
			break;
		}
		ifnet_lock_done(pcb->utun_ifp);
		if (ifnet_dequeue(interface, &data) != 0) {
			break;
		}
		if (utun_output(interface, data) != 0) {
			break;
		}
	}
}
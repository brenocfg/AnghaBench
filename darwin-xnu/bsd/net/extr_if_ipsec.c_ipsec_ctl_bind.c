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
struct sockaddr_ctl {int /*<<< orphan*/  sc_unit; } ;
struct ipsec_pcb {int ipsec_use_netif; int /*<<< orphan*/  ipsec_input_chain_lock; int /*<<< orphan*/  ipsec_pcb_lock; int /*<<< orphan*/  ipsec_rx_fsw_ring_size; int /*<<< orphan*/  ipsec_tx_fsw_ring_size; int /*<<< orphan*/  ipsec_netif_ring_size; int /*<<< orphan*/  ipsec_slot_size; int /*<<< orphan*/  ipsec_output_service_class; int /*<<< orphan*/  ipsec_unit; int /*<<< orphan*/  ipsec_ctlref; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_IF_DEFAULT_RING_SIZE ; 
 int /*<<< orphan*/  IPSEC_IF_DEFAULT_RX_FSW_RING_SIZE ; 
 int /*<<< orphan*/  IPSEC_IF_DEFAULT_SLOT_SIZE ; 
 int /*<<< orphan*/  IPSEC_IF_DEFAULT_TX_FSW_RING_SIZE ; 
 int /*<<< orphan*/  MBUF_SC_OAM ; 
 int /*<<< orphan*/  ipsec_lck_attr ; 
 int /*<<< orphan*/  ipsec_lck_grp ; 
 int /*<<< orphan*/  ipsec_pcb_zone ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ipsec_pcb*,int /*<<< orphan*/ ,int) ; 
 struct ipsec_pcb* zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
ipsec_ctl_bind(kern_ctl_ref kctlref,
			   struct sockaddr_ctl *sac,
			   void **unitinfo)
{
	struct ipsec_pcb *pcb = zalloc(ipsec_pcb_zone);
	memset(pcb, 0, sizeof(*pcb));

	/* Setup the protocol control block */
	*unitinfo = pcb;
	pcb->ipsec_ctlref = kctlref;
	pcb->ipsec_unit = sac->sc_unit;
	pcb->ipsec_output_service_class = MBUF_SC_OAM;

#if IPSEC_NEXUS
	pcb->ipsec_use_netif = false;
	pcb->ipsec_slot_size = IPSEC_IF_DEFAULT_SLOT_SIZE;
	pcb->ipsec_netif_ring_size = IPSEC_IF_DEFAULT_RING_SIZE;
	pcb->ipsec_tx_fsw_ring_size = IPSEC_IF_DEFAULT_TX_FSW_RING_SIZE;
	pcb->ipsec_rx_fsw_ring_size = IPSEC_IF_DEFAULT_RX_FSW_RING_SIZE;
#endif // IPSEC_NEXUS

	lck_rw_init(&pcb->ipsec_pcb_lock, ipsec_lck_grp, ipsec_lck_attr);
#if IPSEC_NEXUS
	lck_mtx_init(&pcb->ipsec_input_chain_lock, ipsec_lck_grp, ipsec_lck_attr);
#endif // IPSEC_NEXUS

	return (0);
}
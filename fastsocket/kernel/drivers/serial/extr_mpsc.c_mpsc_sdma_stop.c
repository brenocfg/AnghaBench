#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct mpsc_port_info {TYPE_1__ port; } ;

/* Variables and functions */
 int SDMA_SDCM_AR ; 
 int SDMA_SDCM_AT ; 
 int /*<<< orphan*/  mpsc_sdma_cmd (struct mpsc_port_info*,int) ; 
 int /*<<< orphan*/  mpsc_sdma_intr_ack (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_sdma_intr_mask (struct mpsc_port_info*,int) ; 
 int /*<<< orphan*/  mpsc_sdma_set_rx_ring (struct mpsc_port_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpsc_sdma_set_tx_ring (struct mpsc_port_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpsc_sdma_stop(struct mpsc_port_info *pi)
{
	pr_debug("mpsc_sdma_stop[%d]: Stopping SDMA\n", pi->port.line);

	/* Abort any SDMA transfers */
	mpsc_sdma_cmd(pi, 0);
	mpsc_sdma_cmd(pi, SDMA_SDCM_AR | SDMA_SDCM_AT);

	/* Clear the SDMA current and first TX and RX pointers */
	mpsc_sdma_set_tx_ring(pi, NULL);
	mpsc_sdma_set_rx_ring(pi, NULL);

	/* Disable interrupts */
	mpsc_sdma_intr_mask(pi, 0xf);
	mpsc_sdma_intr_ack(pi);
}
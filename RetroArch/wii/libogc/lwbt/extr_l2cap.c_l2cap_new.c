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
struct TYPE_2__ {int outmtu; int influshto; int outflushto; int /*<<< orphan*/ * opt; int /*<<< orphan*/  cfgto; int /*<<< orphan*/  inmtu; } ;
struct l2cap_pcb {TYPE_1__ cfg; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  L2CAP_CFG_TO ; 
 int /*<<< orphan*/  L2CAP_CLOSED ; 
 int /*<<< orphan*/  L2CAP_MTU ; 
 struct l2cap_pcb* btmemb_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_pcbs ; 
 int /*<<< orphan*/  memset (struct l2cap_pcb*,int /*<<< orphan*/ ,int) ; 

struct l2cap_pcb* l2cap_new(void)
{
	struct l2cap_pcb *pcb;

	pcb = btmemb_alloc(&l2cap_pcbs);
	if(pcb != NULL) {
		memset(pcb, 0, sizeof(struct l2cap_pcb));
		pcb->state = L2CAP_CLOSED;

		/* Initialize configuration parameter options with default values */

		/* Maximum Transmission Unit */
		pcb->cfg.inmtu = L2CAP_MTU; /* The MTU that this implementation support */
		pcb->cfg.outmtu = 672; /* Default MTU. Two Baseband DH5 packets minus the Baseband ACL headers and
								  L2CAP header. This can be set here since we will never send any signals
								  larger than the L2CAP sig MTU (48 bytes) before L2CAP has been configured
							   */

		/* Flush Timeout */
		pcb->cfg.influshto = 0xFFFF;
		pcb->cfg.outflushto = 0xFFFF;

		pcb->cfg.cfgto = L2CAP_CFG_TO; /* Maximum time before terminating a negotiation.
										  Cfg shall not last more than 120s */
		pcb->cfg.opt = NULL;
		return pcb;
	}
	ERROR("l2cap_new: Could not allocate memory for pcb\n");
	return NULL;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct smc_regs {int smc_smce; } ;
struct scc_regs {int scc_scce; } ;
struct TYPE_9__ {int /*<<< orphan*/  last_active; TYPE_1__* state; } ;
typedef  TYPE_2__ ser_info_t ;
struct TYPE_10__ {struct smc_regs* smc_regs; struct scc_regs* scc_regs; } ;
struct TYPE_8__ {int smc_scc_num; } ;

/* Variables and functions */
 int NUM_IS_SCC ; 
 int PORT_NUM (int) ; 
 int SCCM_RX ; 
 int SCCM_TX ; 
 int SMCM_BRKE ; 
 int SMCM_RX ; 
 int SMCM_TX ; 
 int /*<<< orphan*/  check_modem_status (TYPE_2__*) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_6__* pquicc ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  receive_break (TYPE_2__*) ; 
 int /*<<< orphan*/  receive_chars (TYPE_2__*) ; 
 int /*<<< orphan*/  transmit_chars (TYPE_2__*) ; 

__attribute__((used)) static void rs_360_interrupt(int vec, void *dev_id)
{
	u_char	events;
	int	idx;
	ser_info_t *info;
	volatile struct smc_regs *smcp;
	volatile struct scc_regs *sccp;
	
	info = dev_id;

	idx = PORT_NUM(info->state->smc_scc_num);
	if (info->state->smc_scc_num & NUM_IS_SCC) {
		sccp = &pquicc->scc_regs[idx];
		events = sccp->scc_scce;
		if (events & SCCM_RX)
			receive_chars(info);
		if (events & SCCM_TX)
			transmit_chars(info);
		sccp->scc_scce = events;
	} else {
		smcp = &pquicc->smc_regs[idx];
		events = smcp->smc_smce;
		if (events & SMCM_BRKE)
			receive_break(info);
		if (events & SMCM_RX)
			receive_chars(info);
		if (events & SMCM_TX)
			transmit_chars(info);
		smcp->smc_smce = events;
	}
	
#ifdef SERIAL_DEBUG_INTR
	printk("rs_interrupt_single(%d, %x)...",
					info->state->smc_scc_num, events);
#endif
#ifdef modem_control
	check_modem_status(info);
#endif
	info->last_active = jiffies;
#ifdef SERIAL_DEBUG_INTR
	printk("end.\n");
#endif
}
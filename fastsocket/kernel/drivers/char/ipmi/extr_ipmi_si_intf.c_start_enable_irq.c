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
struct smi_info {int /*<<< orphan*/  si_state; int /*<<< orphan*/  si_sm; TYPE_1__* handlers; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start_transaction ) (int /*<<< orphan*/ ,unsigned char*,int) ;} ;

/* Variables and functions */
 unsigned char IPMI_GET_BMC_GLOBAL_ENABLES_CMD ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int /*<<< orphan*/  SI_ENABLE_INTERRUPTS1 ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void start_enable_irq(struct smi_info *smi_info)
{
	unsigned char msg[2];

	/*
	 * If we are enabling interrupts, we have to tell the
	 * BMC to use them.
	 */
	msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg[1] = IPMI_GET_BMC_GLOBAL_ENABLES_CMD;

	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 2);
	smi_info->si_state = SI_ENABLE_INTERRUPTS1;
}
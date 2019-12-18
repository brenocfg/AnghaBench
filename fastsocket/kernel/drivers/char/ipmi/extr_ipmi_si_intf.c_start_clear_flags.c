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
 unsigned char IPMI_CLEAR_MSG_FLAGS_CMD ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int /*<<< orphan*/  SI_CLEARING_FLAGS ; 
 unsigned char WDT_PRE_TIMEOUT_INT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static void start_clear_flags(struct smi_info *smi_info)
{
	unsigned char msg[3];

	/* Make sure the watchdog pre-timeout flag is not set at startup. */
	msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg[1] = IPMI_CLEAR_MSG_FLAGS_CMD;
	msg[2] = WDT_PRE_TIMEOUT_INT;

	smi_info->handlers->start_transaction(smi_info->si_sm, msg, 3);
	smi_info->si_state = SI_CLEARING_FLAGS;
}
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
typedef  int u32 ;
struct MPT2SAS_ADAPTER {int dummy; } ;

/* Variables and functions */
 int CAN_SLEEP ; 
 int MPI2_IOC_STATE_FAULT ; 
 int mpt2sas_base_get_iocstate (struct MPT2SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
_base_wait_on_iocstate(struct MPT2SAS_ADAPTER *ioc, u32 ioc_state, int timeout,
    int sleep_flag)
{
	u32 count, cntdn;
	u32 current_state;

	count = 0;
	cntdn = (sleep_flag == CAN_SLEEP) ? 1000*timeout : 2000*timeout;
	do {
		current_state = mpt2sas_base_get_iocstate(ioc, 1);
		if (current_state == ioc_state)
			return 0;
		if (count && current_state == MPI2_IOC_STATE_FAULT)
			break;
		if (sleep_flag == CAN_SLEEP)
			msleep(1);
		else
			udelay(500);
		count++;
	} while (--cntdn);

	return current_state;
}
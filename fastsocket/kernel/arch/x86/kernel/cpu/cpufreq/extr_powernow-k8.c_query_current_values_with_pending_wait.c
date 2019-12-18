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
typedef  int u32 ;
struct powernow_k8_data {int currpstate; int numps; int currvid; int currfid; } ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 scalar_t__ CPU_HW_PSTATE ; 
 int HW_PSTATE_0 ; 
 int HW_PSTATE_MASK ; 
 int /*<<< orphan*/  MSR_FIDVID_STATUS ; 
 int /*<<< orphan*/  MSR_PSTATE_STATUS ; 
 int MSR_S_HI_CURRENT_VID ; 
 int MSR_S_LO_CHANGE_PENDING ; 
 int MSR_S_LO_CURRENT_FID ; 
 TYPE_1__ boot_cpu_data ; 
 scalar_t__ cpu_family ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int query_current_values_with_pending_wait(struct powernow_k8_data *data)
{
	u32 lo, hi;
	u32 i = 0;

	if (cpu_family == CPU_HW_PSTATE) {
		rdmsr(MSR_PSTATE_STATUS, lo, hi);
		i = lo & HW_PSTATE_MASK;
		data->currpstate = i;

		/*
		 * a workaround for family 11h erratum 311 might cause
		 * an "out-of-range Pstate if the core is in Pstate-0
		 */
		if ((boot_cpu_data.x86 == 0x11) && (i >= data->numps))
			data->currpstate = HW_PSTATE_0;

		return 0;
	}
	do {
		if (i++ > 10000) {
			dprintk("detected change pending stuck\n");
			return 1;
		}
		rdmsr(MSR_FIDVID_STATUS, lo, hi);
	} while (lo & MSR_S_LO_CHANGE_PENDING);

	data->currvid = hi & MSR_S_HI_CURRENT_VID;
	data->currfid = lo & MSR_S_LO_CURRENT_FID;

	return 0;
}
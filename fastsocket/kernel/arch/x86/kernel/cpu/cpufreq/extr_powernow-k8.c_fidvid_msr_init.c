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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int MSR_C_HI_STP_GNT_BENIGN ; 
 int MSR_C_LO_VID_SHIFT ; 
 int /*<<< orphan*/  MSR_FIDVID_CTL ; 
 int /*<<< orphan*/  MSR_FIDVID_STATUS ; 
 int MSR_S_HI_CURRENT_VID ; 
 int MSR_S_LO_CURRENT_FID ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void fidvid_msr_init(void)
{
	u32 lo, hi;
	u8 fid, vid;

	rdmsr(MSR_FIDVID_STATUS, lo, hi);
	vid = hi & MSR_S_HI_CURRENT_VID;
	fid = lo & MSR_S_LO_CURRENT_FID;
	lo = fid | (vid << MSR_C_LO_VID_SHIFT);
	hi = MSR_C_HI_STP_GNT_BENIGN;
	dprintk("cpu%d, init lo 0x%x, hi 0x%x\n", smp_processor_id(), lo, hi);
	wrmsr(MSR_FIDVID_CTL, lo, hi);
}
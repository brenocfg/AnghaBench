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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_K6_EPMR ; 
 scalar_t__ POWERNOW_IOPORT ; 
 TYPE_1__* clock_ratio ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int powernow_k6_get_cpu_multiplier(void)
{
	u64 invalue = 0;
	u32 msrval;

	msrval = POWERNOW_IOPORT + 0x1;
	wrmsr(MSR_K6_EPMR, msrval, 0); /* enable the PowerNow port */
	invalue = inl(POWERNOW_IOPORT + 0x8);
	msrval = POWERNOW_IOPORT + 0x0;
	wrmsr(MSR_K6_EPMR, msrval, 0); /* disable it again */

	return clock_ratio[(invalue >> 5)&7].index;
}
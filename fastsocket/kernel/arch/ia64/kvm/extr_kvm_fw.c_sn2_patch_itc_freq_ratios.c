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
struct pal_freq_ratio {int num; unsigned long den; } ;
struct ia64_pal_retval {int /*<<< orphan*/  v2; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAL_FREQ_BASE_PLATFORM ; 
 int /*<<< orphan*/  ia64_sal_freq_base (int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int sn_rtc_cycles_per_second ; 

__attribute__((used)) static void sn2_patch_itc_freq_ratios(struct ia64_pal_retval *result)
{
	struct pal_freq_ratio *ratio;
	unsigned long sal_freq, sal_drift, factor;

	result->status = ia64_sal_freq_base(SAL_FREQ_BASE_PLATFORM,
					    &sal_freq, &sal_drift);
	ratio = (struct pal_freq_ratio *)&result->v2;
	factor = ((sal_freq * 3) + (sn_rtc_cycles_per_second / 2)) /
		sn_rtc_cycles_per_second;

	ratio->num = 3;
	ratio->den = factor;
}
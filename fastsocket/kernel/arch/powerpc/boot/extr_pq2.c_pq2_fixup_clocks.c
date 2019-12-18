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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  pq2_get_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq2_set_clocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pq2_fixup_clocks(u32 crystal)
{
	u32 sysfreq, corefreq, timebase, brgfreq;

	if (!pq2_get_clocks(crystal, &sysfreq, &corefreq, &timebase, &brgfreq))
		return 0;

	pq2_set_clocks(sysfreq, corefreq, timebase, brgfreq);
	return 1;
}
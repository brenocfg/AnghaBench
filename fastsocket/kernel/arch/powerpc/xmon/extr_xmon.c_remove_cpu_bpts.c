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

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_IABR ; 
 int /*<<< orphan*/  SPRN_IABR ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dabr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_cpu_bpts(void)
{
	set_dabr(0);
	if (cpu_has_feature(CPU_FTR_IABR))
		mtspr(SPRN_IABR, 0);
}
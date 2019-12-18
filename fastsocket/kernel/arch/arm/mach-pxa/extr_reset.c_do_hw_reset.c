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
 scalar_t__ OSCR ; 
 scalar_t__ OSMR3 ; 
 int /*<<< orphan*/  OSSR ; 
 int /*<<< orphan*/  OSSR_M3 ; 
 int /*<<< orphan*/  OWER ; 
 int /*<<< orphan*/  OWER_WME ; 

__attribute__((used)) static void do_hw_reset(void)
{
	/* Initialize the watchdog and let it fire */
	OWER = OWER_WME;
	OSSR = OSSR_M3;
	OSMR3 = OSCR + 368640;	/* ... in 100 ms */
}
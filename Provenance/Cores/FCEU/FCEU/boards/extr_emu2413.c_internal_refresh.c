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
typedef  void* uint32 ;

/* Variables and functions */
 int AM_DP_WIDTH ; 
 int AM_SPEED ; 
 int PM_DP_WIDTH ; 
 int PM_SPEED ; 
 void* am_dphase ; 
 int clk ; 
 int /*<<< orphan*/  makeDphaseARTable () ; 
 int /*<<< orphan*/  makeDphaseDRTable () ; 
 int /*<<< orphan*/  makeDphaseTable () ; 
 void* pm_dphase ; 
 scalar_t__ rate_adjust (int) ; 

__attribute__((used)) static void internal_refresh(void) {
	makeDphaseTable();
	makeDphaseARTable();
	makeDphaseDRTable();
	pm_dphase = (uint32)rate_adjust(PM_SPEED * PM_DP_WIDTH / (clk / 72));
	am_dphase = (uint32)rate_adjust(AM_SPEED * AM_DP_WIDTH / (clk / 72));
}
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
typedef  scalar_t__ uint32 ;

/* Variables and functions */
 scalar_t__ clk ; 
 int /*<<< orphan*/  internal_refresh () ; 
 int /*<<< orphan*/  makeAdjustTable () ; 
 int /*<<< orphan*/  makeAmTable () ; 
 int /*<<< orphan*/  makeDB2LinTable () ; 
 int /*<<< orphan*/  makePmTable () ; 
 int /*<<< orphan*/  makeRksTable () ; 
 int /*<<< orphan*/  makeSinTable () ; 
 int /*<<< orphan*/  makeTllTable () ; 
 scalar_t__ rate ; 

__attribute__((used)) static void maketables(uint32 c, uint32 r) {
	if (c != clk) {
		clk = c;
		makePmTable();
		makeAmTable();
		makeDB2LinTable();
		makeAdjustTable();
		makeTllTable();
		makeRksTable();
		makeSinTable();
		//makeDefaultPatch ();
	}

	if (r != rate) {
		rate = r;
		internal_refresh();
	}
}
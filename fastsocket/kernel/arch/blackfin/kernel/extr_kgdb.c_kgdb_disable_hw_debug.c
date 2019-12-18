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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSYNC () ; 
 int /*<<< orphan*/  bfin_write_WPDACTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfin_write_WPIACTL (int /*<<< orphan*/ ) ; 

void kgdb_disable_hw_debug(struct pt_regs *regs)
{
	/* Disable hardware debugging while we are in kgdb */
	bfin_write_WPIACTL(0);
	bfin_write_WPDACTL(0);
	CSYNC();
}
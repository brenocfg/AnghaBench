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
struct breakpoint {int /*<<< orphan*/  disposition; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_enable_breakpoint (struct breakpoint*,int /*<<< orphan*/ ) ; 

void
enable_breakpoint (struct breakpoint *bpt)
{
  do_enable_breakpoint (bpt, bpt->disposition);
}
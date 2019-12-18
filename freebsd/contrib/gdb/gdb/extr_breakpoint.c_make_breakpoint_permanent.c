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
struct breakpoint {TYPE_1__* loc; int /*<<< orphan*/  enable_state; } ;
struct TYPE_2__ {int inserted; } ;

/* Variables and functions */
 int /*<<< orphan*/  bp_permanent ; 

void
make_breakpoint_permanent (struct breakpoint *b)
{
  b->enable_state = bp_permanent;

  /* By definition, permanent breakpoints are already present in the code.  */
  b->loc->inserted = 1;
}
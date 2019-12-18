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
typedef  int /*<<< orphan*/  c_pretty_printer ;
struct TYPE_2__ {int /*<<< orphan*/  padding; } ;

/* Variables and functions */
 TYPE_1__* pp_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_none ; 
 int /*<<< orphan*/  pp_right_bracket (int /*<<< orphan*/ *) ; 

void
pp_c_right_bracket (c_pretty_printer *pp)
{
  pp_right_bracket (pp);
  pp_base (pp)->padding = pp_none;
}
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
struct TYPE_2__ {scalar_t__ tail_call_emit; } ;

/* Variables and functions */
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  delete_unreachable_blocks () ; 
 int /*<<< orphan*/  fixup_tail_calls () ; 

__attribute__((used)) static unsigned int
rest_of_handle_jump (void)
{
  delete_unreachable_blocks ();

  if (cfun->tail_call_emit)
    fixup_tail_calls ();
  return 0;
}
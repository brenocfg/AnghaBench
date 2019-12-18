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

__attribute__((used)) static void
do_restore_user_call_depth (void * call_depth)
{	
  int * depth = call_depth;
  /* We will be returning_to_top_level() at this point, so we want to
     reset our depth. */
  (*depth) = 0;
}
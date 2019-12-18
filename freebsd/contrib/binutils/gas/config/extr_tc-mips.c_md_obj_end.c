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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 scalar_t__ cur_proc_ptr ; 

__attribute__((used)) static void
md_obj_end (void)
{
  /* Check for premature end, nesting errors, etc.  */
  if (cur_proc_ptr)
    as_warn (_("missing .end at end of assembly"));
}
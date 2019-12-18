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
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_template_parms ; 
 int /*<<< orphan*/  finish_scope () ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  reset_specialization () ; 

void
end_template_decl (void)
{
  reset_specialization ();

  if (! processing_template_decl)
    return;

  /* This matches the pushlevel in begin_template_parm_list.  */
  finish_scope ();

  --processing_template_decl;
  current_template_parms = TREE_CHAIN (current_template_parms);
}
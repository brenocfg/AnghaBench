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
 int /*<<< orphan*/  arm_rdi_ops ; 
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  remove_breakpoints () ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arm_rdi_mourn_inferior (void)
{
  /* We remove the inserted breakpoints in case the user wants to
     issue another target and load commands to rerun his application;
     This is something that wouldn't work on a native target, for instance,
     as the process goes away when the inferior exits, but it works with
     some remote targets like this one.  That is why this is done here. */
  remove_breakpoints();
  unpush_target (&arm_rdi_ops);
  generic_mourn_inferior ();
}
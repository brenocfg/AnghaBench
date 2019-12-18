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
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  terminal_init_inferior_with_pgrp (int /*<<< orphan*/ ) ; 

void
terminal_init_inferior (void)
{
#ifdef PROCESS_GROUP_TYPE
  /* This is for Lynx, and should be cleaned up by having Lynx be a separate
     debugging target with a version of target_terminal_init_inferior which
     passes in the process group to a generic routine which does all the work
     (and the non-threaded child_terminal_init_inferior can just pass in
     inferior_ptid to the same routine).  */
  /* We assume INFERIOR_PID is also the child's process group.  */
  terminal_init_inferior_with_pgrp (PIDGET (inferior_ptid));
#endif /* PROCESS_GROUP_TYPE */
}
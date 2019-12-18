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
struct TYPE_2__ {int /*<<< orphan*/  (* to_detach ) (char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  blocked_mask ; 
 TYPE_1__ child_ops ; 
 int /*<<< orphan*/  detach_callback ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_lwp_list () ; 
 int /*<<< orphan*/  iterate_over_lwps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  normal_mask ; 
 int /*<<< orphan*/  null_ptid ; 
 int num_lwps ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char*,int) ; 
 int /*<<< orphan*/  trap_ptid ; 

__attribute__((used)) static void
lin_lwp_detach (char *args, int from_tty)
{
  iterate_over_lwps (detach_callback, NULL);

  /* Only the initial process should be left right now.  */
  gdb_assert (num_lwps == 1);

  trap_ptid = null_ptid;

  /* Destroy LWP info; it's no longer valid.  */
  init_lwp_list ();

  /* Restore the original signal mask.  */
  sigprocmask (SIG_SETMASK, &normal_mask, NULL);
  sigemptyset (&blocked_mask);

  inferior_ptid = pid_to_ptid (GET_PID (inferior_ptid));
  child_ops.to_detach (args, from_tty);
}
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
struct TYPE_2__ {int /*<<< orphan*/  (* to_mourn_inferior ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  blocked_mask ; 
 TYPE_1__ child_ops ; 
 int /*<<< orphan*/  init_lwp_list () ; 
 int /*<<< orphan*/  normal_mask ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  trap_ptid ; 

__attribute__((used)) static void
lin_lwp_mourn_inferior (void)
{
  trap_ptid = null_ptid;

  /* Destroy LWP info; it's no longer valid.  */
  init_lwp_list ();

  /* Restore the original signal mask.  */
  sigprocmask (SIG_SETMASK, &normal_mask, NULL);
  sigemptyset (&blocked_mask);

  child_ops.to_mourn_inferior ();
}
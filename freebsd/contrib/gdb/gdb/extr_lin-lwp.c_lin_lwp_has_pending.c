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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int NSIG ; 
 int /*<<< orphan*/  linux_proc_pending_signals (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sigisemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lin_lwp_has_pending (int pid, sigset_t *pending, sigset_t *flush_mask)
{
  sigset_t blocked, ignored;
  int i;

  linux_proc_pending_signals (pid, pending, &blocked, &ignored);

  if (!flush_mask)
    return 0;

  for (i = 1; i < NSIG; i++)
    if (sigismember (pending, i))
      if (!sigismember (flush_mask, i)
	  || sigismember (&blocked, i)
	  || sigismember (&ignored, i))
	sigdelset (pending, i);

  if (sigisemptyset (pending))
    return 0;

  return 1;
}
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
 int THREAD_FETCH_REGISTERS () ; 
 scalar_t__ current_task ; 
 scalar_t__ current_task_id ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  fpregset_saved ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  gregset_saved ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_pc ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supply_gregset (int /*<<< orphan*/ *) ; 
 scalar_t__ thread_support ; 

__attribute__((used)) static int
task_switch (void *tid, void *lwpid)
{
  int res = 0, pid;

  if (thread_support)
    {
      flush_cached_frames ();

      if (current_task != current_task_id)
	{
	  res = THREAD_FETCH_REGISTERS ();
	}
      else
	{
#if (defined(__alpha__) && defined(__osf__) && !defined(VXWORKS_TARGET))
	  supply_gregset (&gregset_saved);
	  supply_fpregset (&fpregset_saved);
#endif
	}

      if (res == 0)
	stop_pc = read_pc ();
      select_frame (get_current_frame ());
      return res;
    }

  return -1;
}
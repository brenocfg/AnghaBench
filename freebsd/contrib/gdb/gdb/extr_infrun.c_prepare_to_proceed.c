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
struct TYPE_2__ {scalar_t__ sig; } ;
struct target_waitstatus {scalar_t__ kind; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ TARGET_SIGNAL_INT ; 
 scalar_t__ TARGET_SIGNAL_TRAP ; 
 scalar_t__ TARGET_WAITKIND_STOPPED ; 
 scalar_t__ breakpoint_here_p (scalar_t__) ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  get_last_target_status (int /*<<< orphan*/ *,struct target_waitstatus*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  minus_one_ptid ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_pc () ; 
 scalar_t__ read_pc_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ ) ; 
 scalar_t__ stop_pc ; 

__attribute__((used)) static int
prepare_to_proceed (void)
{
  ptid_t wait_ptid;
  struct target_waitstatus wait_status;

  /* Get the last target status returned by target_wait().  */
  get_last_target_status (&wait_ptid, &wait_status);

  /* Make sure we were stopped either at a breakpoint, or because
     of a Ctrl-C.  */
  if (wait_status.kind != TARGET_WAITKIND_STOPPED
      || (wait_status.value.sig != TARGET_SIGNAL_TRAP &&
          wait_status.value.sig != TARGET_SIGNAL_INT))
    {
      return 0;
    }

  if (!ptid_equal (wait_ptid, minus_one_ptid)
      && !ptid_equal (inferior_ptid, wait_ptid))
    {
      /* Switched over from WAIT_PID.  */
      CORE_ADDR wait_pc = read_pc_pid (wait_ptid);

      if (wait_pc != read_pc ())
	{
	  /* Switch back to WAIT_PID thread.  */
	  inferior_ptid = wait_ptid;

	  /* FIXME: This stuff came from switch_to_thread() in
	     thread.c (which should probably be a public function).  */
	  flush_cached_frames ();
	  registers_changed ();
	  stop_pc = wait_pc;
	  select_frame (get_current_frame ());
	}

	/* We return 1 to indicate that there is a breakpoint here,
	   so we need to step over it before continuing to avoid
	   hitting it straight away. */
	if (breakpoint_here_p (wait_pc))
	   return 1;
    }

  return 0;
  
}
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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tc_magic_parent ;
typedef  int /*<<< orphan*/  tc_magic_child ;
struct TYPE_2__ {int /*<<< orphan*/ * child_channel; int /*<<< orphan*/ * parent_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUNNING ; 
 size_t SEM_LISTEN ; 
 size_t SEM_TALK ; 
 int /*<<< orphan*/  TT_VERSION ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_thread_info () ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  process_state ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  require_notification_of_exec_events (int) ; 
 TYPE_1__ startup_semaphore ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
child_acknowledge_created_inferior (int pid)
{
  /* We need a memory home for a constant, to pass it to ttrace.
     The value of the constant is arbitrary, so long as both
     parent and child use the same value.  Might as well use the
     "magic" constant provided by ttrace...
   */
  uint64_t tc_magic_parent = TT_VERSION;
  uint64_t tc_magic_child = 0;

  /* Wait for the child to tell us that it has forked. */
  read (startup_semaphore.child_channel[SEM_LISTEN],
	&tc_magic_child,
	sizeof (tc_magic_child));

  /* Clear thread info now.  We'd like to do this in
   * "require...", but that messes up attach.
   */
  clear_thread_info ();

  /* Tell the "rest of gdb" that the initial thread exists.
   * This isn't really a hack.  Other thread-based versions
   * of gdb (e.g. gnu-nat.c) seem to do the same thing.
   *
   * Q: Why don't we also add this thread to the local
   *    list via "add_tthread"?
   *
   * A: Because we don't know the tid, and can't stop the
   *    the process safely to ask what it is.  Anyway, we'll
   *    add it when it gets the EXEC event.
   */
  add_thread (pid_to_ptid (pid));		/* in thread.c */

  /* We can now set the child's ttrace event mask.
   */
  require_notification_of_exec_events (pid);

  /* Tell ourselves that the process is running.
   */
  process_state = RUNNING;

  /* Notify the child that it can exec. */
  write (startup_semaphore.parent_channel[SEM_TALK],
	 &tc_magic_parent,
	 sizeof (tc_magic_parent));

  /* Discard our copy of the semaphore. */
  (void) close (startup_semaphore.parent_channel[SEM_LISTEN]);
  (void) close (startup_semaphore.parent_channel[SEM_TALK]);
  (void) close (startup_semaphore.child_channel[SEM_LISTEN]);
  (void) close (startup_semaphore.child_channel[SEM_TALK]);
}
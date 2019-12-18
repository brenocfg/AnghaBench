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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  tc_magic_parent ;
typedef  int /*<<< orphan*/  tc_magic_child ;
typedef  int /*<<< orphan*/  lwpid_t ;
struct TYPE_2__ {int /*<<< orphan*/ * child_channel; int /*<<< orphan*/ * parent_channel; } ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 size_t SEM_LISTEN ; 
 size_t SEM_TALK ; 
 scalar_t__ TT_NIL ; 
 int /*<<< orphan*/  TT_PROC_SETTRC ; 
 scalar_t__ TT_VERSION ; 
 int call_real_ttrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 TYPE_1__ startup_semaphore ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,scalar_t__*,int) ; 

int
parent_attach_all (int p1, PTRACE_ARG3_TYPE p2, int p3)
{
  int tt_status;

  /* We need a memory home for a constant, to pass it to ttrace.
     The value of the constant is arbitrary, so long as both
     parent and child use the same value.  Might as well use the
     "magic" constant provided by ttrace...
   */
  uint64_t tc_magic_child = TT_VERSION;
  uint64_t tc_magic_parent = 0;

  tt_status = call_real_ttrace (
				 TT_PROC_SETTRC,
				 (int) TT_NIL,
				 (lwpid_t) TT_NIL,
				 TT_NIL,
				 (TTRACE_ARG_TYPE) TT_VERSION,
				 TT_NIL);

  if (tt_status < 0)
    return tt_status;

  /* Notify the parent that we're potentially ready to exec(). */
  write (startup_semaphore.child_channel[SEM_TALK],
	 &tc_magic_child,
	 sizeof (tc_magic_child));

  /* Wait for acknowledgement from the parent. */
  read (startup_semaphore.parent_channel[SEM_LISTEN],
	&tc_magic_parent,
	sizeof (tc_magic_parent));

  if (tc_magic_child != tc_magic_parent)
    warning ("mismatched semaphore magic");

  /* Discard our copy of the semaphore. */
  (void) close (startup_semaphore.parent_channel[SEM_LISTEN]);
  (void) close (startup_semaphore.parent_channel[SEM_TALK]);
  (void) close (startup_semaphore.child_channel[SEM_LISTEN]);
  (void) close (startup_semaphore.child_channel[SEM_TALK]);

  return tt_status;
}
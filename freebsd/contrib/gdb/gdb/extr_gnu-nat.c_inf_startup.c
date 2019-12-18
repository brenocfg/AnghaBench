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
struct inf {int /*<<< orphan*/  event_port; } ;
typedef  scalar_t__ error_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND ; 
 int /*<<< orphan*/  MACH_PORT_RIGHT_RECEIVE ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inf_cleanup (struct inf*) ; 
 int /*<<< orphan*/  inf_debug (struct inf*,char*,int) ; 
 int /*<<< orphan*/  inf_set_pid (struct inf*,int) ; 
 scalar_t__ mach_port_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_port_insert_right (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  safe_strerror (scalar_t__) ; 

void
inf_startup (struct inf *inf, int pid)
{
  error_t err;

  inf_debug (inf, "startup: pid = %d", pid);

  inf_cleanup (inf);

  /* Make the port on which we receive all events.  */
  err = mach_port_allocate (mach_task_self (),
			    MACH_PORT_RIGHT_RECEIVE, &inf->event_port);
  if (err)
    error ("Error allocating event port: %s", safe_strerror (err));

  /* Make a send right for it, so we can easily copy it for other people.  */
  mach_port_insert_right (mach_task_self (), inf->event_port,
			  inf->event_port, MACH_MSG_TYPE_MAKE_SEND);
  inf_set_pid (inf, pid);
}
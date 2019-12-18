#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_3__ {scalar_t__ c_time; int /*<<< orphan*/  c_id; struct TYPE_3__* c_next; } ;
typedef  TYPE_1__ callout ;
struct TYPE_4__ {TYPE_1__* c_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_WARNING ; 
 TYPE_2__ callouts ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ next_softclock ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
reschedule_timeouts(time_t now, time_t then)
{
  callout *cp;

  for (cp = callouts.c_next; cp; cp = cp->c_next) {
    if (cp->c_time >= now && cp->c_time <= then) {
      plog(XLOG_WARNING, "job %d rescheduled to run immediately", cp->c_id);
      dlog("rescheduling job %d back %ld seconds",
	   cp->c_id, (long) (cp->c_time - now));
      next_softclock = cp->c_time = now;
    }
  }
}
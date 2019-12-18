#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* reply; void* handler; } ;
struct TYPE_4__ {int /*<<< orphan*/  kind; } ;
struct TYPE_6__ {TYPE_2__ exc; scalar_t__ thread; TYPE_1__ status; } ;
struct inf {int nomsg; int pause_sc; int want_signals; int want_exceptions; scalar_t__ default_thread_detach_sc; scalar_t__ default_thread_pause_sc; scalar_t__ default_thread_run_sc; scalar_t__ detach_sc; scalar_t__ pending_execs; scalar_t__ no_wait; scalar_t__ traced; scalar_t__ stopped; scalar_t__ running; void* event_port; scalar_t__ signal_thread; scalar_t__ step_thread; TYPE_3__ wait; scalar_t__ pid; scalar_t__ threads_up_to_date; scalar_t__ threads; scalar_t__ task; } ;

/* Variables and functions */
 void* MACH_PORT_NULL ; 
 int /*<<< orphan*/  TARGET_WAITKIND_SPURIOUS ; 
 struct inf* xmalloc (int) ; 

struct inf *
make_inf (void)
{
  struct inf *inf = xmalloc (sizeof (struct inf));

  inf->task = 0;
  inf->threads = 0;
  inf->threads_up_to_date = 0;
  inf->pid = 0;
  inf->wait.status.kind = TARGET_WAITKIND_SPURIOUS;
  inf->wait.thread = 0;
  inf->wait.exc.handler = MACH_PORT_NULL;
  inf->wait.exc.reply = MACH_PORT_NULL;
  inf->step_thread = 0;
  inf->signal_thread = 0;
  inf->event_port = MACH_PORT_NULL;
  inf->running = 0;
  inf->stopped = 0;
  inf->nomsg = 1;
  inf->traced = 0;
  inf->no_wait = 0;
  inf->pending_execs = 0;
  inf->pause_sc = 1;
  inf->detach_sc = 0;
  inf->default_thread_run_sc = 0;
  inf->default_thread_pause_sc = 0;
  inf->default_thread_detach_sc = 0;
  inf->want_signals = 1;	/* By default */
  inf->want_exceptions = 1;	/* By default */

  return inf;
}
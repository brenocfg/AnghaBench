#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  opaque_t ;
typedef  int /*<<< orphan*/  (* callout_fun ) (int /*<<< orphan*/ ) ;
struct TYPE_4__ {scalar_t__ c_time; struct TYPE_4__* c_next; int /*<<< orphan*/  c_arg; int /*<<< orphan*/  (* c_fn ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ callout ;
struct TYPE_5__ {TYPE_1__* c_next; } ;

/* Variables and functions */
 TYPE_3__ callouts ; 
 scalar_t__ clocktime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_task_notify () ; 
 int /*<<< orphan*/  free_callout (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ task_notify_todo ; 

int
softclock(void)
{
  time_t now;
  callout *cp;

  do {
    if (task_notify_todo)
      do_task_notify();

    now = clocktime(NULL);

    /*
     * While there are more callouts waiting...
     */
    while ((cp = callouts.c_next) && cp->c_time <= now) {
      /*
       * Extract first from list, save fn & fn_arg and
       * unlink callout from list and free.
       * Finally call function.
       *
       * The free is done first because
       * it is quite common that the
       * function will call timeout()
       * and try to allocate a callout
       */
      callout_fun *fn = cp->c_fn;
      opaque_t fn_arg = cp->c_arg;

      callouts.c_next = cp->c_next;
      free_callout(cp);
      (*fn) (fn_arg);
    }

  } while (task_notify_todo);

  /*
   * Return number of seconds to next event,
   * or 0 if there is no event.
   */
  if ((cp = callouts.c_next))
    return cp->c_time - now;
  return 0;
}
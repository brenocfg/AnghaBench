#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* gather ) () ;} ;

/* Variables and functions */
 TYPE_1__* impl_current ; 
 TYPE_1__ impl_threaded ; 
 int /*<<< orphan*/  msg_push_bak ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  task_queue_deinit () ; 
 int /*<<< orphan*/  task_queue_init (int,int /*<<< orphan*/ ) ; 
 int task_queue_is_threaded () ; 

void task_queue_check(void)
{
#ifdef HAVE_THREADS
   bool current_threaded = (impl_current == &impl_threaded);
   bool want_threaded    = task_queue_is_threaded();

   if (want_threaded != current_threaded)
      task_queue_deinit();

   if (!impl_current)
      task_queue_init(want_threaded, msg_push_bak);
#endif

   impl_current->gather();
}
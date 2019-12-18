#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ http_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  net_http_update (int /*<<< orphan*/ ,size_t*,size_t*) ; 
 int /*<<< orphan*/  retro_sleep (int) ; 
 scalar_t__ task_queue_is_threaded () ; 
 int /*<<< orphan*/  task_set_progress (TYPE_1__*,int) ; 

__attribute__((used)) static int task_http_iterate_transfer(retro_task_t *task)
{
   http_handle_t *http  = (http_handle_t*)task->state;
   size_t pos  = 0, tot = 0;

   /* FIXME: This wouldn't be needed if we could wait for a timeout */
   if (task_queue_is_threaded())
      retro_sleep(1);

   if (!net_http_update(http->handle, &pos, &tot))
   {
      task_set_progress(task, (tot == 0) ? -1 : (signed)pos / (tot / 100));
      return -1;
   }

   return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  title; int /*<<< orphan*/  callback; int /*<<< orphan*/  handler; int /*<<< orphan*/ * state; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ retro_task_t ;
typedef  int /*<<< orphan*/  retro_task_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_SCANNING_WIRELESS_NETWORKS ; 
 int /*<<< orphan*/  TASK_TYPE_BLOCKING ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 TYPE_1__* task_init () ; 
 int /*<<< orphan*/  task_queue_push (TYPE_1__*) ; 
 int /*<<< orphan*/  task_wifi_scan_handler ; 

bool task_push_wifi_scan(retro_task_callback_t cb)
{
   retro_task_t   *task = task_init();

   if (!task)
      return false;

   /* blocking means no other task can run while this one is running,
    * which is the default */
   task->type           = TASK_TYPE_BLOCKING;
   task->state          = NULL;
   task->handler        = task_wifi_scan_handler;
   task->callback       = cb;
   task->title          = strdup(msg_hash_to_str(
                           MSG_SCANNING_WIRELESS_NETWORKS));

   task_queue_push(task);

   return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_11__ {struct TYPE_11__* msg; } ;
typedef  TYPE_2__ autoconfig_disconnect_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_AUTODETECT ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (TYPE_2__*) ; 
 int /*<<< orphan*/  string_is_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  task_set_finished (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_title (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_autoconfigure_disconnect_handler(retro_task_t *task)
{
   autoconfig_disconnect_t *params = (autoconfig_disconnect_t*)task->state;

   task_set_title(task, strdup(params->msg));

   task_set_finished(task, true);

   RARCH_LOG("%s: %s\n", msg_hash_to_str(MSG_AUTODETECT), params->msg);

   if (!string_is_empty(params->msg))
      free(params->msg);
   free(params);
}
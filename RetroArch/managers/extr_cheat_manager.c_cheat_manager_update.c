#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_5__ {scalar_t__ size; TYPE_1__* cheats; } ;
typedef  TYPE_2__ cheat_manager_t ;
struct TYPE_4__ {char* desc; char* code; scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int,char*,char*) ; 

void cheat_manager_update(cheat_manager_t *handle, unsigned handle_idx)
{
   char msg[256];

   if (!handle || !handle->cheats || handle->size == 0)
      return;

   snprintf(msg, sizeof(msg), "Cheat: #%u [%s]: %s",
         handle_idx, handle->cheats[handle_idx].state ? "ON" : "OFF",
         (handle->cheats[handle_idx].desc != NULL) ?
         (handle->cheats[handle_idx].desc) : (handle->cheats[handle_idx].code)
         );
   runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   RARCH_LOG("%s\n", msg);
}
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
struct TYPE_4__ {scalar_t__ rewind_enable; scalar_t__ cheevos_hardcore_mode_enable; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHEEVOS_LOG (char*,char const*) ; 
 int /*<<< orphan*/  CMD_EVENT_RESET ; 
 int /*<<< orphan*/  CMD_EVENT_REWIND_DEINIT ; 
 int /*<<< orphan*/  CMD_EVENT_REWIND_INIT ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CHEEVOS_HARDCORE_MODE_ENABLE ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* config_get_ptr () ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcheevos_hardcore_paused ; 
 int rcheevos_state_loaded_flag ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char const*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool rcheevos_toggle_hardcore_mode(void)
{
   settings_t *settings = config_get_ptr();

   if (!settings)
      return false;

   /* reset and deinit rewind to avoid cheat the score */
   if (   settings->bools.cheevos_hardcore_mode_enable
       && !rcheevos_hardcore_paused)
   {
      const char *msg = msg_hash_to_str(
            MSG_CHEEVOS_HARDCORE_MODE_ENABLE);

      /* reset the state loaded flag in case it was set */
      rcheevos_state_loaded_flag = false;

      /* send reset core cmd to avoid any user
       * savestate previusly loaded. */
      command_event(CMD_EVENT_RESET, NULL);

      if (settings->bools.rewind_enable)
         command_event(CMD_EVENT_REWIND_DEINIT, NULL);

      CHEEVOS_LOG("%s\n", msg);
      runloop_msg_queue_push(msg, 0, 3 * 60, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   }
   else
   {
      if (settings->bools.rewind_enable)
         command_event(CMD_EVENT_REWIND_INIT, NULL);
   }

   return true;
}
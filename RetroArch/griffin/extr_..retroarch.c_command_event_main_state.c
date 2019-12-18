#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  frame_time_counter_reset_after_load_state; int /*<<< orphan*/  frame_time_counter_reset_after_save_state; } ;
struct TYPE_10__ {int state_slot; } ;
struct TYPE_13__ {TYPE_3__ bools; TYPE_1__ ints; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_14__ {scalar_t__ size; } ;
typedef  TYPE_5__ retro_ctx_size_info_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_11__ {char* savestate; } ;
struct TYPE_15__ {TYPE_2__ name; } ;
typedef  TYPE_6__ global_t ;

/* Variables and functions */
#define  CMD_EVENT_LOAD_STATE 131 
#define  CMD_EVENT_SAVE_STATE 130 
#define  CMD_EVENT_UNDO_LOAD_STATE 129 
#define  CMD_EVENT_UNDO_SAVE_STATE 128 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CORE_DOES_NOT_SUPPORT_SAVESTATES ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  RARCH_NETPLAY_CTL_LOAD_SAVESTATE ; 
 int /*<<< orphan*/  command_event_undo_load_state (char*,int) ; 
 int /*<<< orphan*/  command_event_undo_save_state (char*,int) ; 
 TYPE_4__* configuration_settings ; 
 int /*<<< orphan*/  content_load_state (char*,int,int) ; 
 int /*<<< orphan*/  content_save_state (char*,int,int) ; 
 int /*<<< orphan*/  core_serialize_size (TYPE_5__*) ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,char const*,char*,char,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_6__ g_extern ; 
 scalar_t__ malloc (size_t) ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netplay_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcheevos_hardcore_active ; 
 int rcheevos_state_loaded_flag ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  video_driver_frame_time_count ; 

__attribute__((used)) static bool command_event_main_state(unsigned cmd)
{
   retro_ctx_size_info_t info;
   char msg[128];
   size_t state_path_size     = 16384 * sizeof(char);
   char *state_path           = (char*)malloc(state_path_size);
   const global_t *global     = &g_extern;
   bool ret                   = false;
   bool push_msg              = true;

   state_path[0] = msg[0]     = '\0';

   if (global)
   {
      settings_t *settings       = configuration_settings;
      int state_slot             = settings->ints.state_slot;
      const char *name_savestate = global->name.savestate;

      if (state_slot > 0)
         snprintf(state_path, state_path_size, "%s%d",
               name_savestate, state_slot);
      else if (state_slot < 0)
         fill_pathname_join_delim(state_path,
               name_savestate, "auto", '.', state_path_size);
      else
         strlcpy(state_path, name_savestate, state_path_size);
   }

   core_serialize_size(&info);

   if (info.size)
   {
      switch (cmd)
      {
         case CMD_EVENT_SAVE_STATE:
            content_save_state(state_path, true, false);
            {
               settings_t *settings   = configuration_settings;
               if (settings->bools.frame_time_counter_reset_after_save_state)
                  video_driver_frame_time_count = 0;
            }
            ret      = true;
            push_msg = false;
            break;
         case CMD_EVENT_LOAD_STATE:
            if (content_load_state(state_path, false, false))
            {
#ifdef HAVE_CHEEVOS
               if (rcheevos_hardcore_active)
                  rcheevos_state_loaded_flag = true;
#endif
               ret = true;
#ifdef HAVE_NETWORKING
               netplay_driver_ctl(RARCH_NETPLAY_CTL_LOAD_SAVESTATE, NULL);
#endif
               {
                  settings_t *settings   = configuration_settings;
                  if (settings->bools.frame_time_counter_reset_after_load_state)
                     video_driver_frame_time_count = 0;
               }
            }
            push_msg = false;
            break;
         case CMD_EVENT_UNDO_LOAD_STATE:
            command_event_undo_load_state(msg, sizeof(msg));
            ret = true;
            break;
         case CMD_EVENT_UNDO_SAVE_STATE:
            command_event_undo_save_state(msg, sizeof(msg));
            ret = true;
            break;
      }
   }
   else
      strlcpy(msg, msg_hash_to_str(
               MSG_CORE_DOES_NOT_SUPPORT_SAVESTATES), sizeof(msg));

   if (push_msg)
      runloop_msg_queue_push(msg, 2, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   RARCH_LOG("%s\n", msg);

   free(state_path);
   return ret;
}
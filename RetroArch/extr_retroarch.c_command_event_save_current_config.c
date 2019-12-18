#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
typedef  enum override_type { ____Placeholder_override_type } override_type ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_OVERRIDES_ERROR_SAVING ; 
 int /*<<< orphan*/  MSG_OVERRIDES_SAVED_SUCCESSFULLY ; 
#define  OVERRIDE_CONTENT_DIR 131 
#define  OVERRIDE_CORE 130 
#define  OVERRIDE_GAME 129 
#define  OVERRIDE_NONE 128 
 int /*<<< orphan*/  RARCH_ERR (char*,char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 int /*<<< orphan*/  command_event_save_config (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  config_save_overrides (int) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int runloop_overrides_active ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static void command_event_save_current_config(enum override_type type)
{
   char msg[128];

   msg[0] = '\0';

   switch (type)
   {
      case OVERRIDE_NONE:
         if (path_is_empty(RARCH_PATH_CONFIG))
            strlcpy(msg, "[config] Config directory not set, cannot save configuration.",
                  sizeof(msg));
         else
            command_event_save_config(path_get(RARCH_PATH_CONFIG), msg, sizeof(msg));
         break;
      case OVERRIDE_GAME:
      case OVERRIDE_CORE:
      case OVERRIDE_CONTENT_DIR:
         if (config_save_overrides(type))
         {
            strlcpy(msg, msg_hash_to_str(MSG_OVERRIDES_SAVED_SUCCESSFULLY), sizeof(msg));
            RARCH_LOG("[config] [overrides] %s\n", msg);

            /* set overrides to active so the original config can be
               restored after closing content */
            runloop_overrides_active = true;
         }
         else
         {
            strlcpy(msg, msg_hash_to_str(MSG_OVERRIDES_ERROR_SAVING), sizeof(msg));
            RARCH_ERR("[config] [overrides] %s\n", msg);
         }
         break;
   }

   if (!string_is_empty(msg))
      runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
}
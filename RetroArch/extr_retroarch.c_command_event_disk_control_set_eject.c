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
struct retro_disk_control_callback {scalar_t__ (* set_eject_state ) (int) ;int /*<<< orphan*/  get_num_images; } ;
struct TYPE_3__ {int /*<<< orphan*/  disk_control_cb; } ;
typedef  TYPE_1__ rarch_system_info_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_DISK_CLOSED ; 
 int /*<<< orphan*/  MSG_DISK_EJECTED ; 
 int /*<<< orphan*/  MSG_FAILED_TO ; 
 int /*<<< orphan*/  MSG_VIRTUAL_DISK_TRAY ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ runloop_system ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 scalar_t__ stub1 (int) ; 

__attribute__((used)) static void command_event_disk_control_set_eject(bool new_state, bool print_log)
{
   char msg[128];
   bool error                                        = false;
   const struct retro_disk_control_callback *control = NULL;
   rarch_system_info_t *info                         = &runloop_system;

   msg[0] = '\0';

   if (info)
      control = (const struct retro_disk_control_callback*)&info->disk_control_cb;

   if (!control || !control->get_num_images)
      return;

   if (control->set_eject_state(new_state))
      snprintf(msg, sizeof(msg), "%s %s",
            new_state ?
            msg_hash_to_str(MSG_DISK_EJECTED) :
            msg_hash_to_str(MSG_DISK_CLOSED),
            msg_hash_to_str(MSG_VIRTUAL_DISK_TRAY));
   else
   {
      error = true;
      snprintf(msg, sizeof(msg), "%s %s %s",
            msg_hash_to_str(MSG_FAILED_TO),
            new_state ? "eject" : "close",
            msg_hash_to_str(MSG_VIRTUAL_DISK_TRAY));
   }

   if (!string_is_empty(msg))
   {
      if (error)
         RARCH_ERR("%s\n", msg);
      else
         RARCH_LOG("%s\n", msg);

      /* Only noise in menu. */
      if (print_log)
         runloop_msg_queue_push(msg, 1, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   }
}
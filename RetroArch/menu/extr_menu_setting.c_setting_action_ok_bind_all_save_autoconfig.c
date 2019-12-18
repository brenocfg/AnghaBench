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
struct TYPE_3__ {unsigned int index_offset; } ;
typedef  TYPE_1__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_AUTOCONFIG_FILE_ERROR_SAVING ; 
 int /*<<< orphan*/  MSG_AUTOCONFIG_FILE_SAVED_SUCCESSFULLY ; 
 scalar_t__ config_save_autoconf_profile (char const*,unsigned int) ; 
 char* input_config_get_device_name (unsigned int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static int setting_action_ok_bind_all_save_autoconfig(rarch_setting_t *setting,
      bool wraparound)
{
   unsigned index_offset     = 0;
   const char *name          = NULL;

   (void)wraparound;

   if (!setting)
      return -1;

   index_offset = setting->index_offset;
   name         = input_config_get_device_name(index_offset);

   if(!string_is_empty(name) && config_save_autoconf_profile(name, index_offset))
      runloop_msg_queue_push(
            msg_hash_to_str(MSG_AUTOCONFIG_FILE_SAVED_SUCCESSFULLY), 1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   else
      runloop_msg_queue_push(
            msg_hash_to_str(MSG_AUTOCONFIG_FILE_ERROR_SAVING), 1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

   return 0;
}
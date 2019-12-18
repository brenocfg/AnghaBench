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
typedef  int /*<<< orphan*/  game_path ;
typedef  int /*<<< orphan*/  config_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CORE_OPTIONS_FILE_CREATED_SUCCESSFULLY ; 
 int /*<<< orphan*/  MSG_ERROR_SAVING_CORE_OPTIONS_FILE ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_PATH_CORE_OPTIONS ; 
 int /*<<< orphan*/  config_file_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * config_file_new_alloc () ; 
 int /*<<< orphan*/ * config_file_new_from_path_to_string (char*) ; 
 scalar_t__ config_file_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  retroarch_validate_game_options (char*,int,int) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_ok_option_create(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   char game_path[PATH_MAX_LENGTH];
   config_file_t *conf             = NULL;

   game_path[0] = '\0';

   if (!retroarch_validate_game_options(game_path, sizeof(game_path), true))
   {
      runloop_msg_queue_push(
            msg_hash_to_str(MSG_ERROR_SAVING_CORE_OPTIONS_FILE),
            1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      return 0;
   }

   if (!(conf = config_file_new_from_path_to_string(game_path)))
      if (!(conf = config_file_new_alloc()))
         return false;

   if (config_file_write(conf, game_path, true))
   {
      runloop_msg_queue_push(
            msg_hash_to_str(MSG_CORE_OPTIONS_FILE_CREATED_SUCCESSFULLY),
            1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      path_set(RARCH_PATH_CORE_OPTIONS, game_path);
   }
   config_file_free(conf);

   return 0;
}
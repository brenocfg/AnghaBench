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
struct retro_system_info {int /*<<< orphan*/  library_name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * environ_get; int /*<<< orphan*/ * args; int /*<<< orphan*/ * argv; scalar_t__ argc; } ;
typedef  TYPE_1__ content_ctx_info_t ;
typedef  int /*<<< orphan*/  cdrom_path ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_TYPE_PLAIN ; 
 int /*<<< orphan*/  FRONTEND_FORK_CORE_WITH_ARGS ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_LOAD_CORE_FIRST ; 
 int /*<<< orphan*/  MSG_NO_DISC_INSERTED ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  cdrom_device_fillpath (char*,int,char const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdrom_drive_has_media (char const) ; 
 int /*<<< orphan*/  frontend_driver_set_fork (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char*) ; 
 struct retro_system_info* runloop_get_libretro_system_info () ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_push_load_content_with_core_from_menu (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_ok_load_cdrom(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
#ifdef HAVE_CDROM
   struct retro_system_info *system;

   if (!cdrom_drive_has_media(label[0]))
   {
      RARCH_LOG("[CDROM]: No media is inserted or drive is not ready.\n");

      runloop_msg_queue_push(
            msg_hash_to_str(MSG_NO_DISC_INSERTED),
            1, 100, true,
            NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

      return -1;
   }

   system = runloop_get_libretro_system_info();

   if (system && !string_is_empty(system->library_name))
   {
      char cdrom_path[256] = {0};

      cdrom_device_fillpath(cdrom_path, sizeof(cdrom_path), label[0], 0, true);

      RARCH_LOG("[CDROM]: Loading disc from path: %s\n", cdrom_path);

      path_clear(RARCH_PATH_CONTENT);
      path_set(RARCH_PATH_CONTENT, cdrom_path);

#if defined(HAVE_DYNAMIC)
      {
         content_ctx_info_t content_info;

         content_info.argc        = 0;
         content_info.argv        = NULL;
         content_info.args        = NULL;
         content_info.environ_get = NULL;

         task_push_load_content_with_core_from_menu(cdrom_path, &content_info, CORE_TYPE_PLAIN, NULL, NULL);
      }
#else
      frontend_driver_set_fork(FRONTEND_FORK_CORE_WITH_ARGS);
#endif
   }
   else
   {
      RARCH_LOG("[CDROM]: Cannot load disc without a core.\n");

      runloop_msg_queue_push(
         msg_hash_to_str(MSG_LOAD_CORE_FIRST),
         1, 100, true,
         NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

      return -1;
   }
#endif
   return 0;
}
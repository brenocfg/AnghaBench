#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ core_info_t ;
struct TYPE_8__ {char* system; } ;
struct TYPE_10__ {TYPE_1__ directory; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ core_info_ctx_firmware_t ;
struct TYPE_11__ {char* directory_system; scalar_t__ check_firmware_before_loading; scalar_t__ bios_is_missing; } ;
typedef  TYPE_4__ content_information_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_FIRMWARE ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_CTL_SET_MISSING_BIOS ; 
 int /*<<< orphan*/  RARCH_CTL_UNSET_MISSING_BIOS ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  core_info_get_current_core (TYPE_2__**) ; 
 int /*<<< orphan*/  core_info_list_update_missing_firmware (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_basedir_wrapper (char*) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool firmware_update_status(
      content_information_ctx_t *content_ctx)
{
   core_info_ctx_firmware_t firmware_info;
   bool set_missing_firmware  = false;
   core_info_t *core_info     = NULL;
   size_t s_size              = PATH_MAX_LENGTH * sizeof(char);
   char *s                    = NULL;
   
   core_info_get_current_core(&core_info);

   if (!core_info)
      return false;

   s                          = (char*)malloc(s_size);

   firmware_info.path         = core_info->path;

   if (!string_is_empty(content_ctx->directory_system))
      firmware_info.directory.system = content_ctx->directory_system;
   else
   {
      strlcpy(s, path_get(RARCH_PATH_CONTENT), s_size);
      path_basedir_wrapper(s);
      firmware_info.directory.system = s;
   }

   RARCH_LOG("Updating firmware status for: %s on %s\n",
         core_info->path,
         firmware_info.directory.system);

   rarch_ctl(RARCH_CTL_UNSET_MISSING_BIOS, NULL);

   core_info_list_update_missing_firmware(&firmware_info,
         &set_missing_firmware);

   free(s);

   if (set_missing_firmware)
      rarch_ctl(RARCH_CTL_SET_MISSING_BIOS, NULL);

   if(
         content_ctx->bios_is_missing &&
         content_ctx->check_firmware_before_loading)
   {
      runloop_msg_queue_push(
            msg_hash_to_str(MSG_FIRMWARE),
            100, 500, true, NULL,
            MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
      RARCH_LOG("Load content blocked. Reason: %s\n",
            msg_hash_to_str(MSG_FIRMWARE));

      return true;
   }

   return false;
}
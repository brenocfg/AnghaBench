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
struct retro_game_info {char const* path; int /*<<< orphan*/  member_0; } ;
struct retro_disk_control_callback {unsigned int (* get_num_images ) () ;int /*<<< orphan*/  (* replace_image_index ) (unsigned int,struct retro_game_info*) ;int /*<<< orphan*/  (* add_image_index ) () ;} ;
struct TYPE_3__ {int /*<<< orphan*/  disk_control_cb; } ;
typedef  TYPE_1__ rarch_system_info_t ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_AUTOSAVE_INIT ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_APPENDED_DISK ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  RARCH_PATH_NAMES ; 
 int /*<<< orphan*/  RARCH_PATH_SUBSYSTEM ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_event_disk_control_set_eject (int,int) ; 
 int /*<<< orphan*/  command_event_disk_control_set_index (unsigned int) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_fill_names () ; 
 scalar_t__ path_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  retroarch_autosave_deinit () ; 
 int /*<<< orphan*/  runloop_msg_queue_push (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ runloop_system ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  stub1 () ; 
 unsigned int stub2 () ; 
 int /*<<< orphan*/  stub3 (unsigned int,struct retro_game_info*) ; 

__attribute__((used)) static bool command_event_disk_control_append_image(const char *path)
{
   unsigned new_idx;
   char msg[128];
   struct retro_game_info info                        = {0};
   const struct retro_disk_control_callback *control  = NULL;
   rarch_system_info_t *sysinfo                       = &runloop_system;

   msg[0] = '\0';

   if (sysinfo)
      control = (const struct retro_disk_control_callback*)
         &sysinfo->disk_control_cb;

   if (!control)
      return false;

   command_event_disk_control_set_eject(true, false);

   control->add_image_index();
   new_idx = control->get_num_images();
   if (!new_idx)
      return false;
   new_idx--;

   info.path = path;
   control->replace_image_index(new_idx, &info);

   snprintf(msg, sizeof(msg), "%s: %s", msg_hash_to_str(MSG_APPENDED_DISK), path);
   RARCH_LOG("%s\n", msg);
   runloop_msg_queue_push(msg, 0, 180, true, NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

#ifdef HAVE_THREADS
   retroarch_autosave_deinit();
#endif

   /* TODO: Need to figure out what to do with subsystems case. */
   if (path_is_empty(RARCH_PATH_SUBSYSTEM))
   {
      /* Update paths for our new image.
       * If we actually use append_image, we assume that we
       * started out in a single disk case, and that this way
       * of doing it makes the most sense. */
      path_set(RARCH_PATH_NAMES, path);
      path_fill_names();
   }

   command_event(CMD_EVENT_AUTOSAVE_INIT, NULL);
   command_event_disk_control_set_index(new_idx);
   command_event_disk_control_set_eject(false, false);

   return true;
}
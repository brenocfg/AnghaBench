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
struct retro_disk_control_callback {unsigned int (* get_num_images ) () ;unsigned int (* get_image_index ) () ;} ;
struct TYPE_3__ {struct retro_disk_control_callback disk_control_cb; } ;
typedef  TYPE_1__ rarch_system_info_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NO_DISK ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 TYPE_1__* runloop_get_system_info () ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 unsigned int stub1 () ; 
 unsigned int stub2 () ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_menu_disk_index(
      file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   unsigned images = 0, current                = 0;
   struct retro_disk_control_callback *control = NULL;
   rarch_system_info_t *system                 = runloop_get_system_info();

   if (!system)
      return;

   control = &system->disk_control_cb;

   if (!control)
      return;

   *w = 19;
   *s = '\0';
   strlcpy(s2, path, len2);

   if (!control->get_num_images)
      return;
   if (!control->get_image_index)
      return;

   images  = control->get_num_images();
   current = control->get_image_index();

   if (current >= images)
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_DISK), len);
   else
      snprintf(s, len, "%u", current + 1);
}
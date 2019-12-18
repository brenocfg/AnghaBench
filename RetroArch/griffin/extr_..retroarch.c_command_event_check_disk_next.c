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
struct retro_disk_control_callback {unsigned int (* get_num_images ) () ;unsigned int (* get_image_index ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_GOT_INVALID_DISK_INDEX ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int /*<<< orphan*/ ) ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  command_event_disk_control_set_index (unsigned int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 unsigned int stub1 () ; 
 unsigned int stub2 () ; 

__attribute__((used)) static void command_event_check_disk_next(
      const struct retro_disk_control_callback *control)
{
   unsigned num_disks        = 0;
   unsigned current          = 0;
   bool     disk_next_enable = false;

   if (!control || !control->get_num_images)
      return;
   if (!control->get_image_index)
      return;

   num_disks        = control->get_num_images();
   current          = control->get_image_index();
   disk_next_enable = num_disks && num_disks != UINT_MAX;

   if (!disk_next_enable)
   {
      RARCH_ERR("%s.\n", msg_hash_to_str(MSG_GOT_INVALID_DISK_INDEX));
      return;
   }

   if (current < num_disks - 1)
      current++;
   command_event_disk_control_set_index(current);
}
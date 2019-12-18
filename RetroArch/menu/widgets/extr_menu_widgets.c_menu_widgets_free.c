#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg_widget ;
typedef  int /*<<< orphan*/  menu_widget_msg_t ;
typedef  uintptr_t menu_animation_ctx_tag ;
struct TYPE_8__ {size_t size; } ;
struct TYPE_7__ {int /*<<< orphan*/  carr; } ;
struct TYPE_6__ {int /*<<< orphan*/  carr; } ;

/* Variables and functions */
 TYPE_3__* current_msgs ; 
 int /*<<< orphan*/  fifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 scalar_t__ fifo_read_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_list_free (TYPE_3__*) ; 
 scalar_t__ file_list_get_userdata_at_offset (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  font_driver_bind_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ font_raster_bold ; 
 TYPE_1__ font_raster_regular ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 float generic_message_alpha ; 
 float libretro_message_alpha ; 
 int /*<<< orphan*/  libretro_message_timer ; 
 int /*<<< orphan*/  menu_animation_kill_by_tag (uintptr_t*) ; 
 int /*<<< orphan*/  menu_timer_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_widgets_achievement_free (int /*<<< orphan*/ *) ; 
 uintptr_t menu_widgets_generic_tag ; 
 int /*<<< orphan*/  menu_widgets_msg_queue_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_widgets_screenshot_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msg_queue ; 
 scalar_t__ msg_queue_tasks_count ; 
 float screenshot_alpha ; 
 int /*<<< orphan*/  video_coord_array_free (int /*<<< orphan*/ *) ; 
 float volume_alpha ; 
 uintptr_t volume_tag ; 

void menu_widgets_free(void)
{
   size_t i;
   menu_animation_ctx_tag libretro_tag;

   /* Kill any pending animation */
   menu_animation_kill_by_tag(&volume_tag);
   menu_animation_kill_by_tag(&menu_widgets_generic_tag);

   /* Purge everything from the fifo */
   if (msg_queue)
   {
      while (fifo_read_avail(msg_queue) > 0)
      {
         menu_widget_msg_t *msg_widget;

         fifo_read(msg_queue, &msg_widget, sizeof(msg_widget));

         menu_widgets_msg_queue_free(msg_widget, false);
         free(msg_widget);
      }

      fifo_free(msg_queue);
      msg_queue = NULL;
   }

   /* Purge everything from the list */
   if (current_msgs)
   {
      for (i = 0; i < current_msgs->size; i++)
      {
         menu_widget_msg_t *msg = (menu_widget_msg_t*)
            file_list_get_userdata_at_offset(current_msgs, i);

         menu_widgets_msg_queue_free(msg, false);
      }
      file_list_free(current_msgs);
      current_msgs = NULL;
   }

   msg_queue_tasks_count = 0;

   /* Achievement notification */
   menu_widgets_achievement_free(NULL);

   /* Font */
   video_coord_array_free(&font_raster_regular.carr);
   video_coord_array_free(&font_raster_bold.carr);

   font_driver_bind_block(NULL, NULL);

   /* Reset state of all other widgets */
   /* Generic message*/
   generic_message_alpha = 0.0f;

   /* Libretro message */
   libretro_tag = (uintptr_t) &libretro_message_timer;
   libretro_message_alpha = 0.0f;
   menu_timer_kill(&libretro_message_timer);
   menu_animation_kill_by_tag(&libretro_tag);

   /* AI Service overlay */
   /* ... */

   /* Volume */
   volume_alpha = 0.0f;

   /* Screenshot */
   screenshot_alpha = 0.0f;
   menu_widgets_screenshot_dispose(NULL);
}
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
struct TYPE_6__ {float y; float alpha; float label_alpha; int x; } ;
typedef  TYPE_1__ stripes_node_t ;
struct TYPE_7__ {int icon_size; float items_active_alpha; float margins_screen_top; } ;
typedef  TYPE_2__ stripes_handle_t ;
struct TYPE_8__ {float target_value; float* subject; uintptr_t tag; int /*<<< orphan*/ * cb; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; } ;
typedef  TYPE_3__ menu_animation_ctx_entry_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  STRIPES_DELAY ; 
 size_t file_list_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_3__*) ; 
 int /*<<< orphan*/  video_driver_get_size (int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static void stripes_list_open_old(stripes_handle_t *stripes,
      file_list_t *list, int dir, size_t current)
{
   unsigned i, height = 0;
   int        threshold = stripes->icon_size * 10;
   size_t           end = 0;

   end = file_list_get_size(list);

   video_driver_get_size(NULL, &height);

   for (i = 0; i < end; i++)
   {
      float ia = 0;
      float real_y;
      stripes_node_t *node = (stripes_node_t*)
         file_list_get_userdata_at_offset(list, i);

      if (!node)
         continue;

      if (i == current)
         ia = stripes->items_active_alpha;
      if (dir == -1)
         ia = 0;

      real_y = node->y + stripes->margins_screen_top;

      if (real_y < -threshold || real_y > height+threshold)
      {
         node->alpha = ia;
         node->label_alpha = 0;
         node->x = stripes->icon_size * dir * -2;
      }
      else
      {
         menu_animation_ctx_entry_t anim_entry;

         anim_entry.duration     = STRIPES_DELAY;
         anim_entry.target_value = ia;
         anim_entry.subject      = &node->alpha;
         anim_entry.easing_enum  = EASING_OUT_QUAD;
         anim_entry.tag          = (uintptr_t)list;
         anim_entry.cb           = NULL;

         menu_animation_push(&anim_entry);

         anim_entry.target_value = 0;
         anim_entry.subject      = &node->label_alpha;

         menu_animation_push(&anim_entry);

         anim_entry.target_value = stripes->icon_size * dir * -2;
         anim_entry.subject      = &node->x;

         menu_animation_push(&anim_entry);
      }
   }
}
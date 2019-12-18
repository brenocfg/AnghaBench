#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float alpha; float label_alpha; float zoom; int x; void* y; } ;
typedef  TYPE_1__ stripes_node_t ;
struct TYPE_8__ {float items_passive_alpha; float items_passive_zoom; float items_active_alpha; int depth; int icon_size; int /*<<< orphan*/ * selection_buf_old; scalar_t__ selection_ptr_old; } ;
typedef  TYPE_2__ stripes_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 scalar_t__ file_list_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ menu_entries_get_size () ; 
 size_t menu_navigation_get_selection () ; 
 void* stripes_item_y (TYPE_2__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stripes_layout_ps3 (TYPE_2__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stripes_layout_psp (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 

__attribute__((used)) static void stripes_layout(stripes_handle_t *stripes)
{
   unsigned width, height, i, current, end;
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
   size_t selection           = menu_navigation_get_selection();

   video_driver_get_size(&width, &height);

   /* Mimic the layout of the PSP instead of the PS3 on tiny screens */
   if (width > 320 && height > 240)
      stripes_layout_ps3(stripes, width, height);
   else
      stripes_layout_psp(stripes, width);

   current = (unsigned)selection;
   end     = (unsigned)menu_entries_get_size();

   for (i = 0; i < end; i++)
   {
      float ia         = stripes->items_passive_alpha;
      float iz         = stripes->items_passive_zoom;
      stripes_node_t *node = (stripes_node_t*)file_list_get_userdata_at_offset(
            selection_buf, i);

      if (!node)
         continue;

      if (i == current)
      {
         ia             = stripes->items_active_alpha;
         iz             = stripes->items_active_alpha;
      }

      node->alpha       = ia;
      node->label_alpha = ia;
      node->zoom        = iz;
      node->y           = stripes_item_y(stripes, i, current);
   }

   if (stripes->depth <= 1)
      return;

   current = (unsigned)stripes->selection_ptr_old;
   end     = (unsigned)file_list_get_size(stripes->selection_buf_old);

   for (i = 0; i < end; i++)
   {
      float         ia = 0;
      float         iz = stripes->items_passive_zoom;
      stripes_node_t *node = (stripes_node_t*)file_list_get_userdata_at_offset(
            stripes->selection_buf_old, i);

      if (!node)
         continue;

      if (i == current)
      {
         ia             = stripes->items_active_alpha;
         iz             = stripes->items_active_alpha;
      }

      node->alpha       = ia;
      node->label_alpha = 0;
      node->zoom        = iz;
      node->y           = stripes_item_y(stripes, i, current);
      node->x           = stripes->icon_size * 1 * -2;
   }
}
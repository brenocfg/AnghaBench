#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float alpha; float label_alpha; float zoom; int x; void* y; } ;
typedef  TYPE_2__ xmb_node_t ;
struct TYPE_12__ {int use_ps3_layout; int margins_screen_left; int margins_screen_top; int margins_title_left; int margins_title_top; int margins_title_bottom; int margins_label_left; int margins_label_top; int margins_setting_left; int icon_spacing_horizontal; int icon_spacing_vertical; int icon_size; float items_passive_alpha; float items_passive_zoom; float items_active_alpha; int depth; int /*<<< orphan*/ * selection_buf_old; scalar_t__ selection_ptr_old; } ;
typedef  TYPE_3__ xmb_handle_t ;
struct TYPE_10__ {int menu_xmb_layout; } ;
struct TYPE_13__ {TYPE_1__ uints; } ;
typedef  TYPE_4__ settings_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,int) ; 
 TYPE_4__* config_get_ptr () ; 
 scalar_t__ file_list_get_size (int /*<<< orphan*/ *) ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ menu_entries_get_size () ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  video_driver_get_size (unsigned int*,unsigned int*) ; 
 void* xmb_item_y (TYPE_3__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  xmb_layout_ps3 (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  xmb_layout_psp (TYPE_3__*,unsigned int) ; 

__attribute__((used)) static void xmb_layout(xmb_handle_t *xmb)
{
   unsigned width, height, i, current, end;
   settings_t *settings       = config_get_ptr();
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
   size_t selection           = menu_navigation_get_selection();

   video_driver_get_size(&width, &height);

   switch (settings->uints.menu_xmb_layout)
   {
      /* Automatic */
      case 0:
         {
            xmb->use_ps3_layout        = false;
            xmb->use_ps3_layout        = width > 320 && height > 240;

            /* Mimic the layout of the PSP instead of the PS3 on tiny screens */
            if (xmb->use_ps3_layout)
               xmb_layout_ps3(xmb, width);
            else
               xmb_layout_psp(xmb, width);
         }
         break;
         /* PS3 */
      case 1:
         xmb->use_ps3_layout        = true;
         xmb_layout_ps3(xmb, width);
         break;
         /* PSP */
      case 2:
         xmb->use_ps3_layout        = false;
         xmb_layout_psp(xmb, width);
         break;
   }

#ifdef XMB_DEBUG
   RARCH_LOG("[XMB] margin screen left: %.2f\n",  xmb->margins_screen_left);
   RARCH_LOG("[XMB] margin screen top:  %.2f\n",  xmb->margins_screen_top);
   RARCH_LOG("[XMB] margin title left:  %.2f\n",  xmb->margins_title_left);
   RARCH_LOG("[XMB] margin title top:   %.2f\n",  xmb->margins_title_top);
   RARCH_LOG("[XMB] margin title bott:  %.2f\n",  xmb->margins_title_bottom);
   RARCH_LOG("[XMB] margin label left:  %.2f\n",  xmb->margins_label_left);
   RARCH_LOG("[XMB] margin label top:   %.2f\n",  xmb->margins_label_top);
   RARCH_LOG("[XMB] margin sett left:   %.2f\n",  xmb->margins_setting_left);
   RARCH_LOG("[XMB] icon spacing hor:   %.2f\n",  xmb->icon_spacing_horizontal);
   RARCH_LOG("[XMB] icon spacing ver:   %.2f\n",  xmb->icon_spacing_vertical);
   RARCH_LOG("[XMB] icon size:          %.2f\n",  xmb->icon_size);
#endif

   current = (unsigned)selection;
   end     = (unsigned)menu_entries_get_size();

   for (i = 0; i < end; i++)
   {
      float ia         = xmb->items_passive_alpha;
      float iz         = xmb->items_passive_zoom;
      xmb_node_t *node = (xmb_node_t*)file_list_get_userdata_at_offset(
            selection_buf, i);

      if (!node)
         continue;

      if (i == current)
      {
         ia             = xmb->items_active_alpha;
         iz             = xmb->items_active_alpha;
      }

      node->alpha       = ia;
      node->label_alpha = ia;
      node->zoom        = iz;
      node->y           = xmb_item_y(xmb, i, current);
   }

   if (xmb->depth <= 1)
      return;

   current = (unsigned)xmb->selection_ptr_old;
   end     = (unsigned)file_list_get_size(xmb->selection_buf_old);

   for (i = 0; i < end; i++)
   {
      float         ia = 0;
      float         iz = xmb->items_passive_zoom;
      xmb_node_t *node = (xmb_node_t*)file_list_get_userdata_at_offset(
            xmb->selection_buf_old, i);

      if (!node)
         continue;

      if (i == current)
      {
         ia             = xmb->items_active_alpha;
         iz             = xmb->items_active_alpha;
      }

      node->alpha       = ia;
      node->label_alpha = 0;
      node->zoom        = iz;
      node->y           = xmb_item_y(xmb, i, current);
      node->x           = xmb->icon_size * 1 * -2;
   }
}
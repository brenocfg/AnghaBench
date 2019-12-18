#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float delay_timer; } ;
struct TYPE_6__ {TYPE_4__ secondary; TYPE_4__ primary; } ;
struct TYPE_7__ {TYPE_1__ thumbnails; } ;
typedef  TYPE_2__ materialui_node_t ;
struct TYPE_8__ {scalar_t__ list_view_type; } ;
typedef  TYPE_3__ materialui_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 scalar_t__ MUI_LIST_VIEW_DEFAULT ; 
 scalar_t__ MUI_LIST_VIEW_PLAYLIST ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ materialui_entry_onscreen (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 float menu_thumbnail_get_stream_delay () ; 
 int /*<<< orphan*/  menu_thumbnail_reset (TYPE_4__*) ; 

__attribute__((used)) static void materialui_refresh_thumbnail_image(void *userdata, unsigned i)
{
   materialui_handle_t *mui = (materialui_handle_t*)userdata;

   if (!mui)
      return;

   /* Only refresh thumbnails if we are currently viewing
    * a playlist with thumbnails enabled */
   if ((mui->list_view_type == MUI_LIST_VIEW_DEFAULT) ||
       (mui->list_view_type == MUI_LIST_VIEW_PLAYLIST))
      return;

   /* Only refresh thumbnails if the current entry is
    * on-screen */
   if (materialui_entry_onscreen(mui, (size_t)i))
   {
      file_list_t *list       = menu_entries_get_selection_buf_ptr(0);
      materialui_node_t *node = NULL;
      float stream_delay      = menu_thumbnail_get_stream_delay();

      if (!list)
         return;

      node = (materialui_node_t*)file_list_get_userdata_at_offset(list, (size_t)i);

      if (!node)
         return;

      /* Reset existing thumbnails */
      menu_thumbnail_reset(&node->thumbnails.primary);
      menu_thumbnail_reset(&node->thumbnails.secondary);

      /* No need to actually request thumbnails here
       * > Just set delay timer to the current maximum
       *   value, and thumbnails will be processed via
       *   regular means on the next frame */
      node->thumbnails.primary.delay_timer   = stream_delay;
      node->thumbnails.secondary.delay_timer = stream_delay;
   }
}
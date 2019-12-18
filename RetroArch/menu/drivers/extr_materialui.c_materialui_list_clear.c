#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  secondary; int /*<<< orphan*/  primary; } ;
struct TYPE_8__ {TYPE_1__ thumbnails; } ;
typedef  TYPE_2__ materialui_node_t ;
struct TYPE_9__ {size_t size; } ;
typedef  TYPE_3__ file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_free_userdata (TYPE_3__*,size_t) ; 
 scalar_t__ file_list_get_userdata_at_offset (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  menu_thumbnail_cancel_pending_requests () ; 
 int /*<<< orphan*/  menu_thumbnail_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void materialui_list_clear(file_list_t *list)
{
   size_t i;
   size_t size = list ? list->size : 0;

   /* Must cancel pending thumbnail requests before
    * freeing node->thumbnails objects */
   menu_thumbnail_cancel_pending_requests();

   for (i = 0; i < size; i++)
   {
      materialui_node_t *node = (materialui_node_t*)
            file_list_get_userdata_at_offset(list, i);

      if (!node)
         continue;

      menu_thumbnail_reset(&node->thumbnails.primary);
      menu_thumbnail_reset(&node->thumbnails.secondary);
      file_list_free_userdata(list, i);
   }
}
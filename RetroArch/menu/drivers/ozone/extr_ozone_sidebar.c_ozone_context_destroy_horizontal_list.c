#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  content_icon; int /*<<< orphan*/  icon; } ;
typedef  TYPE_1__ ozone_node_t ;
struct TYPE_6__ {int /*<<< orphan*/  horizontal_list; } ;
typedef  TYPE_2__ ozone_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_LIST_HORIZONTAL ; 
 int /*<<< orphan*/  file_list_get_at_offset (int /*<<< orphan*/ ,unsigned int,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ ,unsigned int) ; 
 size_t ozone_list_get_size (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strstr (char const*,char*) ; 
 int /*<<< orphan*/  video_driver_texture_unload (int /*<<< orphan*/ *) ; 

void ozone_context_destroy_horizontal_list(ozone_handle_t *ozone)
{
   unsigned i;
   size_t list_size = ozone_list_get_size(ozone, MENU_LIST_HORIZONTAL);

   for (i = 0; i < list_size; i++)
   {
      const char *path = NULL;
      ozone_node_t *node = (ozone_node_t*)file_list_get_userdata_at_offset(ozone->horizontal_list, i);

      if (!node)
         continue;

      file_list_get_at_offset(ozone->horizontal_list, i,
            &path, NULL, NULL, NULL);

      if (!path || !strstr(path, ".lpl"))
         continue;

      video_driver_texture_unload(&node->icon);
      video_driver_texture_unload(&node->content_icon);
   }
}
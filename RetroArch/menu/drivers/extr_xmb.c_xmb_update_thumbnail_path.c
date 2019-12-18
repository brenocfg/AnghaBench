#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  thumbnail_path_data; } ;
typedef  TYPE_1__ xmb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_THUMBNAIL_LEFT ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_RIGHT ; 
 int /*<<< orphan*/  menu_thumbnail_get_core_name (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_thumbnail_update_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static void xmb_update_thumbnail_path(void *data, unsigned i, char pos)
{
   xmb_handle_t *xmb     = (xmb_handle_t*)data;
   const char *core_name = NULL;

   if (!xmb)
      return;

   /* imageviewer content requires special treatment... */
   menu_thumbnail_get_core_name(xmb->thumbnail_path_data, &core_name);
   if (string_is_equal(core_name, "imageviewer"))
   {
      if ((pos == 'R') || (pos == 'L' && !menu_thumbnail_is_enabled(xmb->thumbnail_path_data, MENU_THUMBNAIL_RIGHT)))
         menu_thumbnail_update_path(xmb->thumbnail_path_data, pos == 'R' ? MENU_THUMBNAIL_RIGHT : MENU_THUMBNAIL_LEFT);
   }
   else
      menu_thumbnail_update_path(xmb->thumbnail_path_data, pos == 'R' ? MENU_THUMBNAIL_RIGHT : MENU_THUMBNAIL_LEFT);
}
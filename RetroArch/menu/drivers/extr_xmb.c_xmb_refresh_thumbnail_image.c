#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ is_quick_menu; int /*<<< orphan*/  thumbnail_path_data; scalar_t__ is_playlist; scalar_t__ categories_selection_ptr; } ;
typedef  TYPE_1__ xmb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_LIST_PLAIN ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_LEFT ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_RIGHT ; 
 unsigned int XMB_SYSTEM_TAB_SETTINGS ; 
 scalar_t__ menu_thumbnail_is_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int xmb_get_system_tab (TYPE_1__*,unsigned int) ; 
 scalar_t__ xmb_list_get_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmb_update_thumbnail_image (TYPE_1__*) ; 
 int /*<<< orphan*/  xmb_update_thumbnail_path (TYPE_1__*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void xmb_refresh_thumbnail_image(void *data, unsigned i)
{
   xmb_handle_t *xmb                = (xmb_handle_t*)data;

   if (!xmb)
      return;

   /* Only refresh thumbnails if thumbnails are enabled */
   if (  menu_thumbnail_is_enabled(xmb->thumbnail_path_data, MENU_THUMBNAIL_RIGHT) || 
         menu_thumbnail_is_enabled(xmb->thumbnail_path_data, MENU_THUMBNAIL_LEFT))
   {
      unsigned depth          = (unsigned)xmb_list_get_size(xmb, MENU_LIST_PLAIN);
      unsigned xmb_system_tab = xmb_get_system_tab(xmb, (unsigned)xmb->categories_selection_ptr);

      /* Only refresh thumbnails if we are viewing a playlist or
       * the quick menu... */

      /* If we are currently viewing a playlist, then it's almost inevitable
       * that we've just gone up a level from the quick menu. In this case,
       * xmb_set_thumbnail_system() will have been called, which resets
       * thumbnail path data. We therefore have to regenerate the thumbnail
       * paths... */
      if (((xmb_system_tab > XMB_SYSTEM_TAB_SETTINGS && depth == 1) ||
           (xmb_system_tab < XMB_SYSTEM_TAB_SETTINGS && depth == 4)) &&
          xmb->is_playlist)
      {
         if (menu_thumbnail_is_enabled(xmb->thumbnail_path_data, MENU_THUMBNAIL_RIGHT))
            xmb_update_thumbnail_path(xmb, 0 /* will be ignored */, 'R');

         if (menu_thumbnail_is_enabled(xmb->thumbnail_path_data, MENU_THUMBNAIL_LEFT))
            xmb_update_thumbnail_path(xmb, 0 /* will be ignored */, 'L');

         xmb_update_thumbnail_image(xmb);
      }
      else if (xmb->is_quick_menu)
      {
         /* If this is the quick menu (most likely, since this is
          * where the 'download thumbnails' option is located),
          * then thumbnail paths are already valid - just need to
          * update images */
         xmb_update_thumbnail_image(xmb);
      }
   }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t categories_selection_ptr; size_t system_tab_end; int* tabs; int depth; } ;
typedef  TYPE_1__ ozone_handle_t ;

/* Variables and functions */
#define  OZONE_SYSTEM_TAB_ADD 136 
#define  OZONE_SYSTEM_TAB_FAVORITES 135 
#define  OZONE_SYSTEM_TAB_HISTORY 134 
#define  OZONE_SYSTEM_TAB_IMAGES 133 
#define  OZONE_SYSTEM_TAB_MAIN 132 
#define  OZONE_SYSTEM_TAB_MUSIC 131 
#define  OZONE_SYSTEM_TAB_NETPLAY 130 
#define  OZONE_SYSTEM_TAB_SETTINGS 129 
#define  OZONE_SYSTEM_TAB_VIDEO 128 

bool ozone_is_playlist(ozone_handle_t *ozone, bool depth)
{
   bool is_playlist;

   if (ozone->categories_selection_ptr > ozone->system_tab_end)
   {
      is_playlist = true;
   }
   else
   {
      switch (ozone->tabs[ozone->categories_selection_ptr])
      {
         case OZONE_SYSTEM_TAB_MAIN:
         case OZONE_SYSTEM_TAB_SETTINGS:
         case OZONE_SYSTEM_TAB_ADD:
#ifdef HAVE_NETWORKING
         case OZONE_SYSTEM_TAB_NETPLAY:
#endif
            is_playlist = false;
            break;
         case OZONE_SYSTEM_TAB_HISTORY:
         case OZONE_SYSTEM_TAB_FAVORITES:
         case OZONE_SYSTEM_TAB_MUSIC:
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
         case OZONE_SYSTEM_TAB_VIDEO:
#endif
#ifdef HAVE_IMAGEVIEWER
         case OZONE_SYSTEM_TAB_IMAGES:
#endif
         default:
            is_playlist = true;
            break;
      }
   }



   if (depth)
      return is_playlist && ozone->depth == 1;

   return is_playlist;
}
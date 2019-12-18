#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stripes_node_t ;
struct TYPE_5__ {unsigned int system_tab_end; int /*<<< orphan*/  main_menu_node; int /*<<< orphan*/  add_tab_node; int /*<<< orphan*/  netplay_tab_node; int /*<<< orphan*/  favorites_tab_node; int /*<<< orphan*/  history_tab_node; int /*<<< orphan*/  video_tab_node; int /*<<< orphan*/  music_tab_node; int /*<<< orphan*/  images_tab_node; int /*<<< orphan*/  settings_tab_node; } ;
typedef  TYPE_1__ stripes_handle_t ;

/* Variables and functions */
#define  STRIPES_SYSTEM_TAB_ADD 135 
#define  STRIPES_SYSTEM_TAB_FAVORITES 134 
#define  STRIPES_SYSTEM_TAB_HISTORY 133 
#define  STRIPES_SYSTEM_TAB_IMAGES 132 
#define  STRIPES_SYSTEM_TAB_MUSIC 131 
#define  STRIPES_SYSTEM_TAB_NETPLAY 130 
#define  STRIPES_SYSTEM_TAB_SETTINGS 129 
#define  STRIPES_SYSTEM_TAB_VIDEO 128 
 int stripes_get_system_tab (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/ * stripes_get_userdata_from_horizontal_list (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static stripes_node_t* stripes_get_node(stripes_handle_t *stripes, unsigned i)
{
   switch (stripes_get_system_tab(stripes, i))
   {
      case STRIPES_SYSTEM_TAB_SETTINGS:
         return &stripes->settings_tab_node;
#ifdef HAVE_IMAGEVIEWER
      case STRIPES_SYSTEM_TAB_IMAGES:
         return &stripes->images_tab_node;
#endif
      case STRIPES_SYSTEM_TAB_MUSIC:
         return &stripes->music_tab_node;
#ifdef HAVE_FFMPEG
      case STRIPES_SYSTEM_TAB_VIDEO:
         return &stripes->video_tab_node;
#endif
      case STRIPES_SYSTEM_TAB_HISTORY:
         return &stripes->history_tab_node;
      case STRIPES_SYSTEM_TAB_FAVORITES:
         return &stripes->favorites_tab_node;
#ifdef HAVE_NETWORKING
      case STRIPES_SYSTEM_TAB_NETPLAY:
         return &stripes->netplay_tab_node;
#endif
      case STRIPES_SYSTEM_TAB_ADD:
         return &stripes->add_tab_node;
      default:
         if (i > stripes->system_tab_end)
            return stripes_get_userdata_from_horizontal_list(
                  stripes, i - (stripes->system_tab_end + 1));
   }

   return &stripes->main_menu_node;
}
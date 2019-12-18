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
typedef  int /*<<< orphan*/  xmb_node_t ;
struct TYPE_5__ {unsigned int system_tab_end; int /*<<< orphan*/  main_menu_node; int /*<<< orphan*/  add_tab_node; int /*<<< orphan*/  netplay_tab_node; int /*<<< orphan*/  favorites_tab_node; int /*<<< orphan*/  history_tab_node; int /*<<< orphan*/  video_tab_node; int /*<<< orphan*/  music_tab_node; int /*<<< orphan*/  images_tab_node; int /*<<< orphan*/  settings_tab_node; } ;
typedef  TYPE_1__ xmb_handle_t ;

/* Variables and functions */
#define  XMB_SYSTEM_TAB_ADD 135 
#define  XMB_SYSTEM_TAB_FAVORITES 134 
#define  XMB_SYSTEM_TAB_HISTORY 133 
#define  XMB_SYSTEM_TAB_IMAGES 132 
#define  XMB_SYSTEM_TAB_MUSIC 131 
#define  XMB_SYSTEM_TAB_NETPLAY 130 
#define  XMB_SYSTEM_TAB_SETTINGS 129 
#define  XMB_SYSTEM_TAB_VIDEO 128 
 int xmb_get_system_tab (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/ * xmb_get_userdata_from_horizontal_list (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static xmb_node_t* xmb_get_node(xmb_handle_t *xmb, unsigned i)
{
   switch (xmb_get_system_tab(xmb, i))
   {
      case XMB_SYSTEM_TAB_SETTINGS:
         return &xmb->settings_tab_node;
#ifdef HAVE_IMAGEVIEWER
      case XMB_SYSTEM_TAB_IMAGES:
         return &xmb->images_tab_node;
#endif
      case XMB_SYSTEM_TAB_MUSIC:
         return &xmb->music_tab_node;
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
      case XMB_SYSTEM_TAB_VIDEO:
         return &xmb->video_tab_node;
#endif
      case XMB_SYSTEM_TAB_HISTORY:
         return &xmb->history_tab_node;
      case XMB_SYSTEM_TAB_FAVORITES:
         return &xmb->favorites_tab_node;
#ifdef HAVE_NETWORKING
      case XMB_SYSTEM_TAB_NETPLAY:
         return &xmb->netplay_tab_node;
#endif
      case XMB_SYSTEM_TAB_ADD:
         return &xmb->add_tab_node;
      default:
         if (i > xmb->system_tab_end)
            return xmb_get_userdata_from_horizontal_list(
                  xmb, i - (xmb->system_tab_end + 1));
   }

   return &xmb->main_menu_node;
}
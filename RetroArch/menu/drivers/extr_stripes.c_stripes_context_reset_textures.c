#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_23__ {int /*<<< orphan*/ * list; } ;
struct TYPE_22__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_21__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_20__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_19__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_18__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_17__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_16__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_15__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; int /*<<< orphan*/  icon; } ;
struct TYPE_14__ {int /*<<< orphan*/  categories_active_zoom; TYPE_10__ netplay_tab_node; int /*<<< orphan*/  categories_active_alpha; TYPE_9__ textures; TYPE_8__ add_tab_node; TYPE_7__ images_tab_node; TYPE_6__ video_tab_node; TYPE_5__ music_tab_node; TYPE_4__ favorites_tab_node; TYPE_3__ history_tab_node; TYPE_2__ settings_tab_node; TYPE_1__ main_menu_node; } ;
typedef  TYPE_11__ stripes_handle_t ;

/* Variables and functions */
 size_t STRIPES_TEXTURE_ADD ; 
 size_t STRIPES_TEXTURE_FAVORITES ; 
 size_t STRIPES_TEXTURE_HISTORY ; 
 size_t STRIPES_TEXTURE_IMAGES ; 
 unsigned int STRIPES_TEXTURE_LAST ; 
 size_t STRIPES_TEXTURE_MAIN_MENU ; 
 size_t STRIPES_TEXTURE_MOVIES ; 
 size_t STRIPES_TEXTURE_MUSICS ; 
 size_t STRIPES_TEXTURE_NETPLAY ; 
 size_t STRIPES_TEXTURE_SETTINGS ; 
 int /*<<< orphan*/  TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  menu_display_allocate_white_texture () ; 
 int /*<<< orphan*/  menu_display_reset_textures_list (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stripes_texture_path (unsigned int) ; 

__attribute__((used)) static void stripes_context_reset_textures(
      stripes_handle_t *stripes, const char *iconpath)
{
   unsigned i;

   for (i = 0; i < STRIPES_TEXTURE_LAST; i++)
      menu_display_reset_textures_list(stripes_texture_path(i), iconpath, &stripes->textures.list[i], TEXTURE_FILTER_MIPMAP_LINEAR, NULL, NULL);

   menu_display_allocate_white_texture();

   stripes->main_menu_node.icon     = stripes->textures.list[STRIPES_TEXTURE_MAIN_MENU];
   stripes->main_menu_node.alpha    = stripes->categories_active_alpha;
   stripes->main_menu_node.zoom     = stripes->categories_active_zoom;

   stripes->settings_tab_node.icon  = stripes->textures.list[STRIPES_TEXTURE_SETTINGS];
   stripes->settings_tab_node.alpha = stripes->categories_active_alpha;
   stripes->settings_tab_node.zoom  = stripes->categories_active_zoom;

   stripes->history_tab_node.icon   = stripes->textures.list[STRIPES_TEXTURE_HISTORY];
   stripes->history_tab_node.alpha  = stripes->categories_active_alpha;
   stripes->history_tab_node.zoom   = stripes->categories_active_zoom;

   stripes->favorites_tab_node.icon   = stripes->textures.list[STRIPES_TEXTURE_FAVORITES];
   stripes->favorites_tab_node.alpha  = stripes->categories_active_alpha;
   stripes->favorites_tab_node.zoom   = stripes->categories_active_zoom;

   stripes->music_tab_node.icon     = stripes->textures.list[STRIPES_TEXTURE_MUSICS];
   stripes->music_tab_node.alpha    = stripes->categories_active_alpha;
   stripes->music_tab_node.zoom     = stripes->categories_active_zoom;

#ifdef HAVE_FFMPEG
   stripes->video_tab_node.icon     = stripes->textures.list[STRIPES_TEXTURE_MOVIES];
   stripes->video_tab_node.alpha    = stripes->categories_active_alpha;
   stripes->video_tab_node.zoom     = stripes->categories_active_zoom;
#endif

#ifdef HAVE_IMAGEVIEWER
   stripes->images_tab_node.icon    = stripes->textures.list[STRIPES_TEXTURE_IMAGES];
   stripes->images_tab_node.alpha   = stripes->categories_active_alpha;
   stripes->images_tab_node.zoom    = stripes->categories_active_zoom;
#endif

   stripes->add_tab_node.icon       = stripes->textures.list[STRIPES_TEXTURE_ADD];
   stripes->add_tab_node.alpha      = stripes->categories_active_alpha;
   stripes->add_tab_node.zoom       = stripes->categories_active_zoom;

#ifdef HAVE_NETWORKING
   stripes->netplay_tab_node.icon   = stripes->textures.list[STRIPES_TEXTURE_NETPLAY];
   stripes->netplay_tab_node.alpha  = stripes->categories_active_alpha;
   stripes->netplay_tab_node.zoom   = stripes->categories_active_zoom;
#endif
}
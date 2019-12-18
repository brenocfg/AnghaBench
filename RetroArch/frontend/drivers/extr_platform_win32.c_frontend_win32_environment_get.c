#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  menu; } ;
struct TYPE_4__ {TYPE_1__ settings; int /*<<< orphan*/ * dirs; } ;

/* Variables and functions */
 size_t DEFAULT_DIR_ASSETS ; 
 size_t DEFAULT_DIR_AUDIO_FILTER ; 
 size_t DEFAULT_DIR_AUTOCONFIG ; 
 size_t DEFAULT_DIR_CHEATS ; 
 size_t DEFAULT_DIR_CORE ; 
 size_t DEFAULT_DIR_CORE_ASSETS ; 
 size_t DEFAULT_DIR_CORE_INFO ; 
 size_t DEFAULT_DIR_CURSOR ; 
 size_t DEFAULT_DIR_DATABASE ; 
 size_t DEFAULT_DIR_LOGS ; 
 size_t DEFAULT_DIR_MENU_CONFIG ; 
 size_t DEFAULT_DIR_OVERLAY ; 
 size_t DEFAULT_DIR_PLAYLIST ; 
 size_t DEFAULT_DIR_RECORD_CONFIG ; 
 size_t DEFAULT_DIR_RECORD_OUTPUT ; 
 size_t DEFAULT_DIR_REMAP ; 
 size_t DEFAULT_DIR_SAVESTATE ; 
 size_t DEFAULT_DIR_SCREENSHOT ; 
 size_t DEFAULT_DIR_SHADER ; 
 size_t DEFAULT_DIR_SRAM ; 
 size_t DEFAULT_DIR_SYSTEM ; 
 size_t DEFAULT_DIR_THUMBNAILS ; 
 size_t DEFAULT_DIR_VIDEO_FILTER ; 
 size_t DEFAULT_DIR_VIDEO_LAYOUT ; 
 size_t DEFAULT_DIR_WALLPAPERS ; 
 int /*<<< orphan*/  fill_pathname_expand_special (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__ g_defaults ; 
 int /*<<< orphan*/  gfx_set_dwm () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void frontend_win32_environment_get(int *argc, char *argv[],
      void *args, void *params_data)
{
   gfx_set_dwm();

   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_ASSETS],
      ":\\assets", sizeof(g_defaults.dirs[DEFAULT_DIR_ASSETS]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_AUDIO_FILTER],
      ":\\filters\\audio", sizeof(g_defaults.dirs[DEFAULT_DIR_AUDIO_FILTER]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_VIDEO_FILTER],
      ":\\filters\\video", sizeof(g_defaults.dirs[DEFAULT_DIR_VIDEO_FILTER]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_CHEATS],
      ":\\cheats", sizeof(g_defaults.dirs[DEFAULT_DIR_CHEATS]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_DATABASE],
      ":\\database\\rdb", sizeof(g_defaults.dirs[DEFAULT_DIR_DATABASE]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_CURSOR],
      ":\\database\\cursors", sizeof(g_defaults.dirs[DEFAULT_DIR_CURSOR]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_PLAYLIST],
      ":\\playlists", sizeof(g_defaults.dirs[DEFAULT_DIR_ASSETS]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_RECORD_CONFIG],
      ":\\config\\record", sizeof(g_defaults.dirs[DEFAULT_DIR_RECORD_CONFIG]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_RECORD_OUTPUT],
      ":\\recordings", sizeof(g_defaults.dirs[DEFAULT_DIR_RECORD_OUTPUT]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_MENU_CONFIG],
      ":\\config", sizeof(g_defaults.dirs[DEFAULT_DIR_MENU_CONFIG]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_REMAP],
      ":\\config\\remaps", sizeof(g_defaults.dirs[DEFAULT_DIR_REMAP]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_WALLPAPERS],
      ":\\assets\\wallpapers", sizeof(g_defaults.dirs[DEFAULT_DIR_WALLPAPERS]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_THUMBNAILS],
      ":\\thumbnails", sizeof(g_defaults.dirs[DEFAULT_DIR_THUMBNAILS]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_OVERLAY],
      ":\\overlays", sizeof(g_defaults.dirs[DEFAULT_DIR_OVERLAY]));
#ifdef HAVE_VIDEO_LAYOUT
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_VIDEO_LAYOUT],
      ":\\layouts", sizeof(g_defaults.dirs[DEFAULT_DIR_VIDEO_LAYOUT]));
#endif
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_CORE],
      ":\\cores", sizeof(g_defaults.dirs[DEFAULT_DIR_CORE]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_CORE_INFO],
      ":\\info", sizeof(g_defaults.dirs[DEFAULT_DIR_CORE_INFO]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_AUTOCONFIG],
      ":\\autoconfig", sizeof(g_defaults.dirs[DEFAULT_DIR_AUTOCONFIG]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_SHADER],
      ":\\shaders", sizeof(g_defaults.dirs[DEFAULT_DIR_SHADER]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_CORE_ASSETS],
      ":\\downloads", sizeof(g_defaults.dirs[DEFAULT_DIR_CORE_ASSETS]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_SCREENSHOT],
      ":\\screenshots", sizeof(g_defaults.dirs[DEFAULT_DIR_SCREENSHOT]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_SRAM],
      ":\\saves", sizeof(g_defaults.dirs[DEFAULT_DIR_SRAM]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_SAVESTATE],
      ":\\states", sizeof(g_defaults.dirs[DEFAULT_DIR_SAVESTATE]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_SYSTEM],
      ":\\system", sizeof(g_defaults.dirs[DEFAULT_DIR_SYSTEM]));
   fill_pathname_expand_special(g_defaults.dirs[DEFAULT_DIR_LOGS],
      ":\\logs", sizeof(g_defaults.dirs[DEFAULT_DIR_LOGS]));
#ifdef HAVE_MENU
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGLES) || defined(HAVE_OPENGL_CORE)
   strlcpy(g_defaults.settings.menu, "xmb", sizeof(g_defaults.settings.menu));
#endif
#endif
}
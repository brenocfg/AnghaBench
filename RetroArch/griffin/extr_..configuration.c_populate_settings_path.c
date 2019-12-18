#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct config_path_setting {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  log_dir; int /*<<< orphan*/  directory_screenshot; int /*<<< orphan*/  directory_video_layout; int /*<<< orphan*/  directory_overlay; int /*<<< orphan*/  directory_menu_config; int /*<<< orphan*/  directory_menu_content; int /*<<< orphan*/  directory_audio_filter; int /*<<< orphan*/  directory_autoconfig; int /*<<< orphan*/  directory_runtime_log; int /*<<< orphan*/  directory_playlist; int /*<<< orphan*/  directory_thumbnails; int /*<<< orphan*/  directory_dynamic_wallpapers; int /*<<< orphan*/  directory_assets; int /*<<< orphan*/  directory_core_assets; int /*<<< orphan*/  directory_video_filter; int /*<<< orphan*/  directory_video_shader; int /*<<< orphan*/  directory_resampler; int /*<<< orphan*/  directory_input_remapping; int /*<<< orphan*/  directory_cache; int /*<<< orphan*/  directory_system; int /*<<< orphan*/  directory_content_history; int /*<<< orphan*/  directory_cursor; int /*<<< orphan*/  path_font; int /*<<< orphan*/  path_stream_url; int /*<<< orphan*/  path_stream_config; int /*<<< orphan*/  path_record_config; int /*<<< orphan*/  path_video_layout; int /*<<< orphan*/  path_overlay; int /*<<< orphan*/  path_content_image_history; int /*<<< orphan*/  path_content_video_history; int /*<<< orphan*/  path_content_music_history; int /*<<< orphan*/  path_content_favorites; int /*<<< orphan*/  path_content_history; int /*<<< orphan*/  path_rgui_theme_preset; int /*<<< orphan*/  path_menu_wallpaper; int /*<<< orphan*/  path_cheat_database; int /*<<< orphan*/  path_content_database; int /*<<< orphan*/  path_libretro_info; int /*<<< orphan*/  path_core_options; int /*<<< orphan*/  directory_libretro; int /*<<< orphan*/  netplay_spectate_password; int /*<<< orphan*/  netplay_password; int /*<<< orphan*/  netplay_server; int /*<<< orphan*/  network_buildbot_assets_url; int /*<<< orphan*/  network_buildbot_url; int /*<<< orphan*/  path_audio_dsp_plugin; int /*<<< orphan*/  path_softfilter_plugin; int /*<<< orphan*/  username; int /*<<< orphan*/  kiosk_mode_password; int /*<<< orphan*/  menu_content_show_settings_password; int /*<<< orphan*/  path_menu_xmb_font; } ;
struct TYPE_9__ {TYPE_2__ paths; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_7__ {int /*<<< orphan*/  config_dir; int /*<<< orphan*/  output_dir; } ;
struct TYPE_10__ {TYPE_1__ record; } ;
typedef  TYPE_4__ global_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_DIR_SAVEFILE ; 
 int /*<<< orphan*/  RARCH_DIR_SAVESTATE ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 int /*<<< orphan*/  SETTING_ARRAY (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SETTING_PATH (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dir_get_ptr (int /*<<< orphan*/ ) ; 
 TYPE_4__* global_get_ptr () ; 
 int /*<<< orphan*/  path_get_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct config_path_setting *populate_settings_path(settings_t *settings, int *size)
{
   unsigned count = 0;
   struct config_path_setting  *tmp    = (struct config_path_setting*)calloc(1, (*size + 1) * sizeof(struct config_path_setting));

   if (!tmp)
      return NULL;

   /* Paths */
#ifdef HAVE_XMB
   SETTING_PATH("xmb_font",                   settings->paths.path_menu_xmb_font, false, NULL, true);
#endif
   SETTING_PATH("content_show_settings_password", settings->paths.menu_content_show_settings_password, false, NULL, true);
   SETTING_PATH("kiosk_mode_password",        settings->paths.kiosk_mode_password, false, NULL, true);
   SETTING_PATH("netplay_nickname",           settings->paths.username, false, NULL, true);
   SETTING_PATH("video_filter",               settings->paths.path_softfilter_plugin, false, NULL, true);
   SETTING_PATH("audio_dsp_plugin",           settings->paths.path_audio_dsp_plugin, false, NULL, true);
   SETTING_PATH("core_updater_buildbot_cores_url", settings->paths.network_buildbot_url, false, NULL, true);
   SETTING_PATH("core_updater_buildbot_assets_url", settings->paths.network_buildbot_assets_url, false, NULL, true);
#ifdef HAVE_NETWORKING
   SETTING_PATH("netplay_ip_address",       settings->paths.netplay_server, false, NULL, true);
   SETTING_PATH("netplay_password",           settings->paths.netplay_password, false, NULL, true);
   SETTING_PATH("netplay_spectate_password",  settings->paths.netplay_spectate_password, false, NULL, true);
#endif
   SETTING_PATH("libretro_directory",
         settings->paths.directory_libretro, false, NULL, false);
   SETTING_PATH("core_options_path",
         settings->paths.path_core_options, false, NULL, true);
   SETTING_PATH("libretro_info_path",
         settings->paths.path_libretro_info, false, NULL, true);
   SETTING_PATH("content_database_path",
         settings->paths.path_content_database, false, NULL, true);
   SETTING_PATH("cheat_database_path",
         settings->paths.path_cheat_database, false, NULL, true);
#ifdef HAVE_MENU
   SETTING_PATH("menu_wallpaper",
         settings->paths.path_menu_wallpaper, false, NULL, true);
   SETTING_PATH("rgui_menu_theme_preset",
         settings->paths.path_rgui_theme_preset, false, NULL, true);
#endif
   SETTING_PATH("content_history_path",
         settings->paths.path_content_history, false, NULL, true);
   SETTING_PATH("content_favorites_path",
         settings->paths.path_content_favorites, false, NULL, true);
   SETTING_PATH("content_music_history_path",
         settings->paths.path_content_music_history, false, NULL, true);
   SETTING_PATH("content_video_history_path",
         settings->paths.path_content_video_history, false, NULL, true);
   SETTING_PATH("content_image_history_path",
         settings->paths.path_content_image_history, false, NULL, true);
#ifdef HAVE_OVERLAY
   SETTING_PATH("input_overlay",
         settings->paths.path_overlay, false, NULL, true);
#endif
#ifdef HAVE_VIDEO_LAYOUT
   SETTING_PATH("video_layout_path",
         settings->paths.path_video_layout, false, NULL, true);
   SETTING_PATH("video_layout_directory",
         settings->paths.directory_video_layout, true, NULL, true);
#endif
   SETTING_PATH("video_record_config",
         settings->paths.path_record_config, false, NULL, true);
   SETTING_PATH("video_stream_config",
         settings->paths.path_stream_config, false, NULL, true);
   SETTING_PATH("video_stream_url",
         settings->paths.path_stream_url, false, NULL, true);
   SETTING_PATH("video_font_path",
         settings->paths.path_font, false, NULL, true);
   SETTING_PATH("cursor_directory",
         settings->paths.directory_cursor, false, NULL, true);
   SETTING_PATH("content_history_dir",
         settings->paths.directory_content_history, false, NULL, true);
   SETTING_PATH("screenshot_directory",
         settings->paths.directory_screenshot, true, NULL, true);
   SETTING_PATH("system_directory",
         settings->paths.directory_system, true, NULL, true);
   SETTING_PATH("cache_directory",
         settings->paths.directory_cache, false, NULL, true);
   SETTING_PATH("input_remapping_directory",
         settings->paths.directory_input_remapping, false, NULL, true);
   SETTING_PATH("resampler_directory",
         settings->paths.directory_resampler, false, NULL, true);
   SETTING_PATH("video_shader_dir",
         settings->paths.directory_video_shader, true, NULL, true);
   SETTING_PATH("video_filter_dir",
         settings->paths.directory_video_filter, true, NULL, true);
   SETTING_PATH("core_assets_directory",
         settings->paths.directory_core_assets, true, NULL, true);
   SETTING_PATH("assets_directory",
         settings->paths.directory_assets, true, NULL, true);
   SETTING_PATH("dynamic_wallpapers_directory",
         settings->paths.directory_dynamic_wallpapers, true, NULL, true);
   SETTING_PATH("thumbnails_directory",
         settings->paths.directory_thumbnails, true, NULL, true);
   SETTING_PATH("playlist_directory",
         settings->paths.directory_playlist, true, NULL, true);
   SETTING_PATH("runtime_log_directory",
         settings->paths.directory_runtime_log, true, NULL, true);
   SETTING_PATH("joypad_autoconfig_dir",
         settings->paths.directory_autoconfig, false, NULL, true);
   SETTING_PATH("audio_filter_dir",
         settings->paths.directory_audio_filter, true, NULL, true);
   SETTING_PATH("savefile_directory",
         dir_get_ptr(RARCH_DIR_SAVEFILE), true, NULL, false);
   SETTING_PATH("savestate_directory",
         dir_get_ptr(RARCH_DIR_SAVESTATE), true, NULL, false);
#ifdef HAVE_MENU
   SETTING_PATH("rgui_browser_directory",
         settings->paths.directory_menu_content, true, NULL, true);
   SETTING_PATH("rgui_config_directory",
         settings->paths.directory_menu_config, true, NULL, true);
#endif
#ifdef HAVE_OVERLAY
   SETTING_PATH("overlay_directory",
         settings->paths.directory_overlay, true, NULL, true);
#endif
#ifdef HAVE_VIDEO_LAYOUT
   SETTING_PATH("video_layout_directory",
         settings->paths.directory_video_layout, true, NULL, true);
#endif
#ifndef HAVE_DYNAMIC
   SETTING_PATH("libretro_path",
         path_get_ptr(RARCH_PATH_CORE), false, NULL, false);
#endif
   SETTING_PATH(
         "screenshot_directory",
         settings->paths.directory_screenshot, true, NULL, false);

   {
      global_t   *global                  = global_get_ptr();
      if (global)
      {
         SETTING_PATH("recording_output_directory",
               global->record.output_dir, false, NULL, true);
         SETTING_PATH("recording_config_directory",
               global->record.config_dir, false, NULL, true);
      }
   }

   SETTING_ARRAY("log_dir", settings->paths.log_dir, true, NULL, true);

   *size = count;

   return tmp;
}
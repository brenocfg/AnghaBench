#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct config_array_setting {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ai_service_url; int /*<<< orphan*/  discord_app_id; int /*<<< orphan*/  twitch_stream_key; int /*<<< orphan*/  youtube_stream_key; int /*<<< orphan*/  midi_output; int /*<<< orphan*/  midi_input; int /*<<< orphan*/  midi_driver; int /*<<< orphan*/  netplay_mitm_server; int /*<<< orphan*/  led_driver; int /*<<< orphan*/  bundle_assets_dst_subdir; int /*<<< orphan*/  bundle_assets_dst; int /*<<< orphan*/  bundle_assets_src; int /*<<< orphan*/  input_keyboard_layout; int /*<<< orphan*/  input_joypad_driver; int /*<<< orphan*/  input_driver; int /*<<< orphan*/  audio_resampler; int /*<<< orphan*/  audio_driver; int /*<<< orphan*/  video_context_driver; int /*<<< orphan*/  cheevos_token; int /*<<< orphan*/  cheevos_password; int /*<<< orphan*/  cheevos_username; int /*<<< orphan*/  camera_device; int /*<<< orphan*/  audio_device; int /*<<< orphan*/  menu_driver; int /*<<< orphan*/  location_driver; int /*<<< orphan*/  wifi_driver; int /*<<< orphan*/  camera_driver; int /*<<< orphan*/  record_driver; int /*<<< orphan*/  video_driver; } ;
struct TYPE_5__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DEFAULT_AI_SERVICE_URL ; 
 int /*<<< orphan*/  SETTING_ARRAY (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/ * default_discord_app_id ; 
 int /*<<< orphan*/ * midi_input ; 
 int /*<<< orphan*/ * midi_output ; 

__attribute__((used)) static struct config_array_setting *populate_settings_array(settings_t *settings, int *size)
{
   unsigned count                        = 0;
   struct config_array_setting  *tmp    = (struct config_array_setting*)calloc(1, (*size + 1) * sizeof(struct config_array_setting));

   if (!tmp)
      return NULL;

   /* Arrays */
   SETTING_ARRAY("video_driver",             settings->arrays.video_driver,   false, NULL, true);
   SETTING_ARRAY("record_driver",            settings->arrays.record_driver,  false, NULL, true);
   SETTING_ARRAY("camera_driver",            settings->arrays.camera_driver,  false, NULL, true);
   SETTING_ARRAY("wifi_driver",              settings->arrays.wifi_driver,    false, NULL, true);
   SETTING_ARRAY("location_driver",          settings->arrays.location_driver,false, NULL, true);
#ifdef HAVE_MENU
   SETTING_ARRAY("menu_driver",              settings->arrays.menu_driver,    false, NULL, true);
#endif
   SETTING_ARRAY("audio_device",             settings->arrays.audio_device,   false, NULL, true);
   SETTING_ARRAY("camera_device",            settings->arrays.camera_device,  false, NULL, true);
#ifdef HAVE_CHEEVOS
   SETTING_ARRAY("cheevos_username",         settings->arrays.cheevos_username, false, NULL, true);
   SETTING_ARRAY("cheevos_password",         settings->arrays.cheevos_password, false, NULL, true);
   SETTING_ARRAY("cheevos_token",            settings->arrays.cheevos_token, false, NULL, true);
#endif
   SETTING_ARRAY("video_context_driver",     settings->arrays.video_context_driver,   false, NULL, true);
   SETTING_ARRAY("audio_driver",             settings->arrays.audio_driver,           false, NULL, true);
   SETTING_ARRAY("audio_resampler",          settings->arrays.audio_resampler,        false, NULL, true);
   SETTING_ARRAY("input_driver",             settings->arrays.input_driver,           false, NULL, true);
   SETTING_ARRAY("input_joypad_driver",      settings->arrays.input_joypad_driver,    false, NULL, true);
   SETTING_ARRAY("input_keyboard_layout",    settings->arrays.input_keyboard_layout,  false, NULL, true);
   SETTING_ARRAY("bundle_assets_src_path",   settings->arrays.bundle_assets_src, false, NULL, true);
   SETTING_ARRAY("bundle_assets_dst_path",   settings->arrays.bundle_assets_dst, false, NULL, true);
   SETTING_ARRAY("bundle_assets_dst_path_subdir", settings->arrays.bundle_assets_dst_subdir, false, NULL, true);
   SETTING_ARRAY("led_driver",               settings->arrays.led_driver, false, NULL, true);
   SETTING_ARRAY("netplay_mitm_server",      settings->arrays.netplay_mitm_server, false, NULL, true);
   SETTING_ARRAY("midi_driver",              settings->arrays.midi_driver, false, NULL, true);
   SETTING_ARRAY("midi_input",               settings->arrays.midi_input, true, midi_input, true);
   SETTING_ARRAY("midi_output",              settings->arrays.midi_output, true, midi_output, true);
   SETTING_ARRAY("youtube_stream_key",       settings->arrays.youtube_stream_key, true, NULL, true);
   SETTING_ARRAY("twitch_stream_key",       settings->arrays.twitch_stream_key, true, NULL, true);
   SETTING_ARRAY("discord_app_id",           settings->arrays.discord_app_id, true, default_discord_app_id, true);
   SETTING_ARRAY("ai_service_url",           settings->arrays.ai_service_url, true, DEFAULT_AI_SERVICE_URL, true);

   *size = count;

   return tmp;
}
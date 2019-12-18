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
struct config_float_setting {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  video_msg_bgcolor_opacity; int /*<<< orphan*/  input_analog_sensitivity; int /*<<< orphan*/  input_analog_deadzone; int /*<<< orphan*/  slowmotion_ratio; int /*<<< orphan*/  fastforward_ratio; int /*<<< orphan*/  video_font_size; int /*<<< orphan*/  video_msg_pos_y; int /*<<< orphan*/  video_msg_pos_x; int /*<<< orphan*/  menu_rgui_particle_effect_speed; int /*<<< orphan*/  menu_ticker_speed; int /*<<< orphan*/  menu_header_opacity; int /*<<< orphan*/  menu_footer_opacity; int /*<<< orphan*/  menu_framebuffer_opacity; int /*<<< orphan*/  menu_wallpaper_opacity; int /*<<< orphan*/  menu_scale_factor; int /*<<< orphan*/  input_overlay_scale; int /*<<< orphan*/  input_overlay_opacity; int /*<<< orphan*/  audio_mixer_volume; int /*<<< orphan*/  audio_volume; int /*<<< orphan*/  audio_max_timing_skew; int /*<<< orphan*/  video_refresh_rate; int /*<<< orphan*/  crt_video_refresh_rate; int /*<<< orphan*/  video_scale; int /*<<< orphan*/  video_aspect_ratio; } ;
struct TYPE_5__ {TYPE_1__ floats; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ACTION_RATE_CONTROL_DELTA ; 
 float DEFAULT_ASPECT_RATIO ; 
 float DEFAULT_AUDIO_MIXER_VOLUME ; 
 float DEFAULT_AUDIO_VOLUME ; 
 float DEFAULT_CRT_REFRESH_RATE ; 
 float DEFAULT_FASTFORWARD_RATIO ; 
 float DEFAULT_FONT_SIZE ; 
 float DEFAULT_INPUT_OVERLAY_OPACITY ; 
 float DEFAULT_MAX_TIMING_SKEW ; 
 float DEFAULT_MENU_SCALE_FACTOR ; 
 float DEFAULT_RATE_CONTROL_DELTA ; 
 float DEFAULT_REFRESH_RATE ; 
 float DEFAULT_RGUI_PARTICLE_EFFECT_SPEED ; 
 float DEFAULT_SLOWMOTION_RATIO ; 
 int /*<<< orphan*/  INPUT_ACTION_AXIS_THRESHOLD ; 
 int /*<<< orphan*/  SETTING_FLOAT (char*,int /*<<< orphan*/ *,int,float,int) ; 
 float analog_deadzone ; 
 float analog_sensitivity ; 
 int /*<<< orphan*/ * audio_get_float_ptr (int /*<<< orphan*/ ) ; 
 float axis_threshold ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/ * input_driver_get_float (int /*<<< orphan*/ ) ; 
 float menu_footer_opacity ; 
 float menu_framebuffer_opacity ; 
 float menu_header_opacity ; 
 float menu_ticker_speed ; 
 float menu_wallpaper_opacity ; 
 float message_bgcolor_opacity ; 
 float message_pos_offset_x ; 
 float message_pos_offset_y ; 

__attribute__((used)) static struct config_float_setting *populate_settings_float(settings_t *settings, int *size)
{
   unsigned count = 0;
   struct config_float_setting  *tmp      = (struct config_float_setting*)calloc(1, (*size + 1) * sizeof(struct config_float_setting));

   if (!tmp)
      return NULL;

   SETTING_FLOAT("video_aspect_ratio",       &settings->floats.video_aspect_ratio, true, DEFAULT_ASPECT_RATIO, false);
   SETTING_FLOAT("video_scale",              &settings->floats.video_scale, false, 0.0f, false);
   SETTING_FLOAT("crt_video_refresh_rate",   &settings->floats.crt_video_refresh_rate, true, DEFAULT_CRT_REFRESH_RATE, false);
   SETTING_FLOAT("video_refresh_rate",       &settings->floats.video_refresh_rate, true, DEFAULT_REFRESH_RATE, false);
   SETTING_FLOAT("audio_rate_control_delta", audio_get_float_ptr(AUDIO_ACTION_RATE_CONTROL_DELTA), true, DEFAULT_RATE_CONTROL_DELTA, false);
   SETTING_FLOAT("audio_max_timing_skew",    &settings->floats.audio_max_timing_skew, true, DEFAULT_MAX_TIMING_SKEW, false);
   SETTING_FLOAT("audio_volume",             &settings->floats.audio_volume, true, DEFAULT_AUDIO_VOLUME, false);
#ifdef HAVE_AUDIOMIXER
   SETTING_FLOAT("audio_mixer_volume",       &settings->floats.audio_mixer_volume, true, DEFAULT_AUDIO_MIXER_VOLUME, false);
#endif
#ifdef HAVE_OVERLAY
   SETTING_FLOAT("input_overlay_opacity",    &settings->floats.input_overlay_opacity, true, DEFAULT_INPUT_OVERLAY_OPACITY, false);
   SETTING_FLOAT("input_overlay_scale",      &settings->floats.input_overlay_scale, true, 1.0f, false);
#endif
#ifdef HAVE_MENU
   SETTING_FLOAT("menu_scale_factor",        &settings->floats.menu_scale_factor, true, DEFAULT_MENU_SCALE_FACTOR, false);
   SETTING_FLOAT("menu_wallpaper_opacity",   &settings->floats.menu_wallpaper_opacity, true, menu_wallpaper_opacity, false);
   SETTING_FLOAT("menu_framebuffer_opacity", &settings->floats.menu_framebuffer_opacity, true, menu_framebuffer_opacity, false);
   SETTING_FLOAT("menu_footer_opacity",      &settings->floats.menu_footer_opacity,    true, menu_footer_opacity, false);
   SETTING_FLOAT("menu_header_opacity",      &settings->floats.menu_header_opacity,    true, menu_header_opacity, false);
   SETTING_FLOAT("menu_ticker_speed",        &settings->floats.menu_ticker_speed,      true, menu_ticker_speed,   false);
   SETTING_FLOAT("rgui_particle_effect_speed", &settings->floats.menu_rgui_particle_effect_speed, true, DEFAULT_RGUI_PARTICLE_EFFECT_SPEED, false);
#endif
   SETTING_FLOAT("video_message_pos_x",      &settings->floats.video_msg_pos_x,      true, message_pos_offset_x, false);
   SETTING_FLOAT("video_message_pos_y",      &settings->floats.video_msg_pos_y,      true, message_pos_offset_y, false);
   SETTING_FLOAT("video_font_size",          &settings->floats.video_font_size,      true, DEFAULT_FONT_SIZE, false);
   SETTING_FLOAT("fastforward_ratio",        &settings->floats.fastforward_ratio,    true, DEFAULT_FASTFORWARD_RATIO, false);
   SETTING_FLOAT("slowmotion_ratio",         &settings->floats.slowmotion_ratio,     true, DEFAULT_SLOWMOTION_RATIO, false);
   SETTING_FLOAT("input_axis_threshold",     input_driver_get_float(INPUT_ACTION_AXIS_THRESHOLD), true, axis_threshold, false);
   SETTING_FLOAT("input_analog_deadzone",    &settings->floats.input_analog_deadzone, true, analog_deadzone, false);
   SETTING_FLOAT("input_analog_sensitivity",    &settings->floats.input_analog_sensitivity, true, analog_sensitivity, false);
   SETTING_FLOAT("video_msg_bgcolor_opacity", &settings->floats.video_msg_bgcolor_opacity, true, message_bgcolor_opacity, false);

   *size = count;

   return tmp;
}
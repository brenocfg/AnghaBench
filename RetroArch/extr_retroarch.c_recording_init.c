#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct video_viewport {unsigned int width; unsigned int height; scalar_t__ full_height; scalar_t__ full_width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_16__ {scalar_t__ sample_rate; scalar_t__ fps; } ;
struct TYPE_15__ {unsigned int base_width; unsigned int base_height; void* max_height; void* max_width; } ;
struct retro_system_av_info {TYPE_4__ timing; TYPE_3__ geometry; } ;
struct record_params {unsigned int out_width; unsigned int out_height; int channels; char* filename; int preset; float aspect_ratio; void* pix_fmt; void* fb_height; void* fb_width; int /*<<< orphan*/ * config; scalar_t__ samplerate; scalar_t__ fps; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {scalar_t__ video_post_filter_record; scalar_t__ video_force_aspect; scalar_t__ video_gpu_record; } ;
struct TYPE_14__ {int video_stream_port; scalar_t__ video_record_quality; scalar_t__ video_stream_quality; } ;
struct TYPE_18__ {int /*<<< orphan*/ * path_record_config; int /*<<< orphan*/ * path_stream_config; int /*<<< orphan*/ * path_stream_url; } ;
struct TYPE_19__ {TYPE_1__ bools; TYPE_2__ uints; TYPE_6__ paths; } ;
typedef  TYPE_7__ settings_t ;
typedef  int /*<<< orphan*/  output ;
struct TYPE_17__ {int /*<<< orphan*/ * config; int /*<<< orphan*/  output_dir; int /*<<< orphan*/ * path; } ;
struct TYPE_20__ {TYPE_5__ record; } ;
typedef  TYPE_8__ global_t ;
typedef  enum record_config_type { ____Placeholder_record_config_type } record_config_type ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_12__ {scalar_t__ read_viewport; } ;

/* Variables and functions */
 scalar_t__ CORE_TYPE_DUMMY ; 
 void* FFEMU_PIX_ARGB8888 ; 
 void* FFEMU_PIX_BGR24 ; 
 void* FFEMU_PIX_RGB565 ; 
 int /*<<< orphan*/  MSG_CUSTOM_TIMING_GIVEN ; 
 int /*<<< orphan*/  MSG_DETECTED_VIEWPORT_OF ; 
 int /*<<< orphan*/  MSG_FAILED_TO_START_RECORDING ; 
 int /*<<< orphan*/  MSG_HW_RENDERED_MUST_USE_POSTSHADED_RECORDING ; 
 int /*<<< orphan*/  MSG_RECORDING_TO ; 
 int /*<<< orphan*/  MSG_USING_LIBRETRO_DUMMY_CORE_RECORDING_SKIPPED ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  RARCH_PATH_BASENAME ; 
 int /*<<< orphan*/  RARCH_WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ RECORD_CONFIG_TYPE_RECORDING_APNG ; 
 scalar_t__ RECORD_CONFIG_TYPE_RECORDING_GIF ; 
 scalar_t__ RECORD_CONFIG_TYPE_RECORDING_WEBM_FAST ; 
 scalar_t__ RETRO_PIXEL_FORMAT_XRGB8888 ; 
 TYPE_7__* configuration_settings ; 
 scalar_t__ current_core_type ; 
 TYPE_10__* current_video ; 
 int /*<<< orphan*/  fill_pathname_join (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fill_str_dated_filename (char*,char const*,char*,int) ; 
 TYPE_8__ g_extern ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 void* next_pow2 (unsigned int) ; 
 char* path_basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rarch_softfilter_get_max_output_size (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  record_driver_init_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct record_params*) ; 
 int /*<<< orphan*/  recording_data ; 
 int /*<<< orphan*/  recording_driver ; 
 int /*<<< orphan*/  recording_enable ; 
 float recording_gpu_height ; 
 unsigned int recording_gpu_width ; 
 unsigned int recording_height ; 
 unsigned int recording_width ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ streaming_enable ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,int) ; 
 float video_driver_aspect_ratio ; 
 struct retro_system_av_info video_driver_av_info ; 
 int /*<<< orphan*/  video_driver_get_viewport_info (struct video_viewport*) ; 
 int /*<<< orphan*/  video_driver_gpu_record_deinit () ; 
 int /*<<< orphan*/  video_driver_gpu_record_init (unsigned int) ; 
 scalar_t__ video_driver_is_hw_context () ; 
 scalar_t__ video_driver_pix_fmt ; 
 int /*<<< orphan*/  video_driver_state_filter ; 
 scalar_t__ video_driver_state_out_rgb32 ; 

__attribute__((used)) static bool recording_init(void)
{
   char output[PATH_MAX_LENGTH];
   char buf[PATH_MAX_LENGTH];
   struct record_params params          = {0};
   struct retro_system_av_info *av_info = &video_driver_av_info;
   settings_t *settings                 = configuration_settings;
   global_t *global                     = &g_extern;

   if (!recording_enable)
      return false;

   output[0] = '\0';

   if (current_core_type == CORE_TYPE_DUMMY)
   {
      RARCH_WARN("[recording] %s\n",
            msg_hash_to_str(MSG_USING_LIBRETRO_DUMMY_CORE_RECORDING_SKIPPED));
      return false;
   }

   if (!settings->bools.video_gpu_record
         && video_driver_is_hw_context())
   {
      RARCH_WARN("[recording] %s.\n",
            msg_hash_to_str(MSG_HW_RENDERED_MUST_USE_POSTSHADED_RECORDING));
      return false;
   }

   RARCH_LOG("[recording] %s: FPS: %.4f, Sample rate: %.4f\n",
         msg_hash_to_str(MSG_CUSTOM_TIMING_GIVEN),
         (float)av_info->timing.fps,
         (float)av_info->timing.sample_rate);

   if (!string_is_empty(global->record.path))
      strlcpy(output, global->record.path, sizeof(output));
   else
   {
      if (streaming_enable)
         if (!string_is_empty(settings->paths.path_stream_url))
            strlcpy(output, settings->paths.path_stream_url, sizeof(output));
         else
            /* Fallback, stream locally to 127.0.0.1 */
            snprintf(output, sizeof(output), "udp://127.0.0.1:%u", settings->uints.video_stream_port);
      else
      {
         const char *game_name = path_basename(path_get(RARCH_PATH_BASENAME));
         if (settings->uints.video_record_quality < RECORD_CONFIG_TYPE_RECORDING_WEBM_FAST)
         {
            fill_str_dated_filename(buf, game_name,
                     "mkv", sizeof(buf));
            fill_pathname_join(output, global->record.output_dir, buf, sizeof(output));
         }
         else if (settings->uints.video_record_quality >= RECORD_CONFIG_TYPE_RECORDING_WEBM_FAST
               && settings->uints.video_record_quality < RECORD_CONFIG_TYPE_RECORDING_GIF)
         {
            fill_str_dated_filename(buf, game_name,
                     "webm", sizeof(buf));
            fill_pathname_join(output, global->record.output_dir, buf, sizeof(output));
         }
         else if (settings->uints.video_record_quality >= RECORD_CONFIG_TYPE_RECORDING_GIF
               && settings->uints.video_record_quality < RECORD_CONFIG_TYPE_RECORDING_APNG)
         {
            fill_str_dated_filename(buf, game_name,
                     "gif", sizeof(buf));
            fill_pathname_join(output, global->record.output_dir, buf, sizeof(output));
         }
         else
         {
            fill_str_dated_filename(buf, game_name,
                     "png", sizeof(buf));
            fill_pathname_join(output, global->record.output_dir, buf, sizeof(output));
         }
      }
   }

   params.out_width  = av_info->geometry.base_width;
   params.out_height = av_info->geometry.base_height;
   params.fb_width   = av_info->geometry.max_width;
   params.fb_height  = av_info->geometry.max_height;
   params.channels   = 2;
   params.filename   = output;
   params.fps        = av_info->timing.fps;
   params.samplerate = av_info->timing.sample_rate;
   params.pix_fmt    = (video_driver_pix_fmt == RETRO_PIXEL_FORMAT_XRGB8888)
      ? FFEMU_PIX_ARGB8888
      : FFEMU_PIX_RGB565;
   params.config     = NULL;

   if (!string_is_empty(global->record.config))
      params.config = global->record.config;
   else
   {
      if (streaming_enable)
      {
         params.config = settings->paths.path_stream_config;
         params.preset = (enum record_config_type)
            settings->uints.video_stream_quality;
      }
      else
      {
         params.config = settings->paths.path_record_config;
         params.preset = (enum record_config_type)
            settings->uints.video_record_quality;
      }
   }

   if (settings->bools.video_gpu_record
      && current_video->read_viewport)
   {
      unsigned gpu_size;
      struct video_viewport vp;

      vp.x                        = 0;
      vp.y                        = 0;
      vp.width                    = 0;
      vp.height                   = 0;
      vp.full_width               = 0;
      vp.full_height              = 0;

      video_driver_get_viewport_info(&vp);

      if (!vp.width || !vp.height)
      {
         RARCH_ERR("[recording] Failed to get viewport information from video driver. "
               "Cannot start recording ...\n");
         return false;
      }

      params.out_width  = vp.width;
      params.out_height = vp.height;
      params.fb_width   = next_pow2(vp.width);
      params.fb_height  = next_pow2(vp.height);

      if (settings->bools.video_force_aspect &&
            (video_driver_aspect_ratio > 0.0f))
         params.aspect_ratio  = video_driver_aspect_ratio;
      else
         params.aspect_ratio  = (float)vp.width / vp.height;

      params.pix_fmt             = FFEMU_PIX_BGR24;
      recording_gpu_width        = vp.width;
      recording_gpu_height       = vp.height;

      RARCH_LOG("[recording] %s %u x %u\n", msg_hash_to_str(MSG_DETECTED_VIEWPORT_OF),
            vp.width, vp.height);

      gpu_size = vp.width * vp.height * 3;
      if (!video_driver_gpu_record_init(gpu_size))
         return false;
   }
   else
   {
      if (recording_width || recording_height)
      {
         params.out_width  = recording_width;
         params.out_height = recording_height;
      }

      if (settings->bools.video_force_aspect &&
            (video_driver_aspect_ratio > 0.0f))
         params.aspect_ratio = video_driver_aspect_ratio;
      else
         params.aspect_ratio = (float)params.out_width / params.out_height;

      if (settings->bools.video_post_filter_record
            && !!video_driver_state_filter)
      {
         unsigned max_width  = 0;
         unsigned max_height = 0;

         params.pix_fmt    = FFEMU_PIX_RGB565;

         if (video_driver_state_out_rgb32)
            params.pix_fmt = FFEMU_PIX_ARGB8888;

         rarch_softfilter_get_max_output_size(
               video_driver_state_filter,
               &max_width, &max_height);
         params.fb_width  = next_pow2(max_width);
         params.fb_height = next_pow2(max_height);
      }
   }

   RARCH_LOG("[recording] %s %s @ %ux%u. (FB size: %ux%u pix_fmt: %u)\n",
         msg_hash_to_str(MSG_RECORDING_TO),
         output,
         params.out_width, params.out_height,
         params.fb_width, params.fb_height,
         (unsigned)params.pix_fmt);

   if (!record_driver_init_first(&recording_driver, &recording_data, &params))
   {
      RARCH_ERR("[recording] %s\n", msg_hash_to_str(MSG_FAILED_TO_START_RECORDING));
      video_driver_gpu_record_deinit();

      return false;
   }

   return true;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_53__   TYPE_9__ ;
typedef  struct TYPE_52__   TYPE_8__ ;
typedef  struct TYPE_51__   TYPE_7__ ;
typedef  struct TYPE_50__   TYPE_6__ ;
typedef  struct TYPE_49__   TYPE_5__ ;
typedef  struct TYPE_48__   TYPE_4__ ;
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_2__ ;
typedef  struct TYPE_45__   TYPE_23__ ;
typedef  struct TYPE_44__   TYPE_1__ ;
typedef  struct TYPE_43__   TYPE_19__ ;
typedef  struct TYPE_42__   TYPE_18__ ;
typedef  struct TYPE_41__   TYPE_17__ ;
typedef  struct TYPE_40__   TYPE_16__ ;
typedef  struct TYPE_39__   TYPE_15__ ;
typedef  struct TYPE_38__   TYPE_14__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fps_range ;
typedef  int /*<<< orphan*/  camera_num ;
typedef  int /*<<< orphan*/  cam_config ;
struct TYPE_53__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_52__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_51__ {int member_0; int member_1; } ;
struct TYPE_50__ {int member_0; int member_1; } ;
struct TYPE_49__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_47__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_48__ {TYPE_3__ previewWindow; } ;
struct TYPE_46__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_45__ {int shutter_speed; int /*<<< orphan*/  stereo_mode; } ;
struct TYPE_44__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_43__ {TYPE_14__* control; TYPE_14__** output; int /*<<< orphan*/  output_num; } ;
struct TYPE_42__ {TYPE_11__* es; void* encoding; int /*<<< orphan*/  encoding_variant; } ;
struct TYPE_41__ {int one_shot_stills; int num_preview_video_frames; int /*<<< orphan*/  hdr; int /*<<< orphan*/  max_preview_video_h; int /*<<< orphan*/  max_preview_video_w; int /*<<< orphan*/  use_stc_timestamp; int /*<<< orphan*/  fast_preview_resume; int /*<<< orphan*/  stills_capture_circular_buffer_height; int /*<<< orphan*/  stills_yuv422; int /*<<< orphan*/  max_stills_h; int /*<<< orphan*/  max_stills_w; TYPE_2__ member_0; } ;
struct TYPE_40__ {int /*<<< orphan*/  hdr; TYPE_7__ member_2; TYPE_6__ member_1; TYPE_5__ member_0; } ;
struct TYPE_39__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct TYPE_38__ {scalar_t__ buffer_num; TYPE_18__* format; } ;
struct TYPE_36__ {scalar_t__ verbose; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sensor_mode; int /*<<< orphan*/  cameraNum; } ;
struct TYPE_37__ {TYPE_12__ common_settings; TYPE_19__* camera_component; int /*<<< orphan*/  raspitex_state; scalar_t__ useGL; TYPE_23__ camera_parameters; TYPE_4__ preview_parameters; scalar_t__ fullResPreview; } ;
struct TYPE_34__ {TYPE_9__ frame_rate; TYPE_8__ crop; void* height; void* width; } ;
struct TYPE_35__ {TYPE_10__ video; } ;
typedef  TYPE_13__ RASPISTILL_STATE ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_14__ MMAL_PORT_T ;
typedef  TYPE_15__ MMAL_PARAMETER_INT32_T ;
typedef  TYPE_16__ MMAL_PARAMETER_FPS_RANGE_T ;
typedef  TYPE_17__ MMAL_PARAMETER_CAMERA_CONFIG_T ;
typedef  TYPE_18__ MMAL_ES_FORMAT_T ;
typedef  TYPE_19__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_RES_PREVIEW_FRAME_RATE_DEN ; 
 int /*<<< orphan*/  FULL_RES_PREVIEW_FRAME_RATE_NUM ; 
 size_t MMAL_CAMERA_CAPTURE_PORT ; 
 size_t MMAL_CAMERA_PREVIEW_PORT ; 
 size_t MMAL_CAMERA_VIDEO_PORT ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CAMERA ; 
 int /*<<< orphan*/  MMAL_ENCODING_I420 ; 
 void* MMAL_ENCODING_OPAQUE ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_CONFIG ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_CUSTOM_SENSOR_CONFIG ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_NUM ; 
 int /*<<< orphan*/  MMAL_PARAMETER_FPS_RANGE ; 
 int /*<<< orphan*/  MMAL_PARAM_TIMESTAMP_MODE_RESET_STC ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  PREVIEW_FRAME_RATE_DEN ; 
 int /*<<< orphan*/  PREVIEW_FRAME_RATE_NUM ; 
 int /*<<< orphan*/  STILLS_FRAME_RATE_DEN ; 
 int /*<<< orphan*/  STILLS_FRAME_RATE_NUM ; 
 void* VCOS_ALIGN_UP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ VIDEO_OUTPUT_BUFFERS_NUM ; 
 int /*<<< orphan*/  default_camera_control_callback ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mmal_component_create (int /*<<< orphan*/ ,TYPE_19__**) ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_19__*) ; 
 scalar_t__ mmal_component_enable (TYPE_19__*) ; 
 int /*<<< orphan*/  mmal_format_full_copy (TYPE_18__*,TYPE_18__*) ; 
 scalar_t__ mmal_port_enable (TYPE_14__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_format_commit (TYPE_14__*) ; 
 scalar_t__ mmal_port_parameter_set (TYPE_14__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_parameter_set_uint32 (TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raspicamcontrol_set_all_parameters (TYPE_19__*,TYPE_23__*) ; 
 scalar_t__ raspicamcontrol_set_stereo_mode (TYPE_14__*,int /*<<< orphan*/ *) ; 
 scalar_t__ raspitex_configure_preview_port (int /*<<< orphan*/ *,TYPE_14__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vcos_log_error (char*,...) ; 

__attribute__((used)) static MMAL_STATUS_T create_camera_component(RASPISTILL_STATE *state)
{
   MMAL_COMPONENT_T *camera = 0;
   MMAL_ES_FORMAT_T *format;
   MMAL_PORT_T *preview_port = NULL, *video_port = NULL, *still_port = NULL;
   MMAL_STATUS_T status;

   /* Create the component */
   status = mmal_component_create(MMAL_COMPONENT_DEFAULT_CAMERA, &camera);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("Failed to create camera component");
      goto error;
   }

   status = raspicamcontrol_set_stereo_mode(camera->output[0], &state->camera_parameters.stereo_mode);
   status += raspicamcontrol_set_stereo_mode(camera->output[1], &state->camera_parameters.stereo_mode);
   status += raspicamcontrol_set_stereo_mode(camera->output[2], &state->camera_parameters.stereo_mode);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("Could not set stereo mode : error %d", status);
      goto error;
   }

   MMAL_PARAMETER_INT32_T camera_num =
   {{MMAL_PARAMETER_CAMERA_NUM, sizeof(camera_num)}, state->common_settings.cameraNum};

   status = mmal_port_parameter_set(camera->control, &camera_num.hdr);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("Could not select camera : error %d", status);
      goto error;
   }

   if (!camera->output_num)
   {
      status = MMAL_ENOSYS;
      vcos_log_error("Camera doesn't have output ports");
      goto error;
   }

   status = mmal_port_parameter_set_uint32(camera->control, MMAL_PARAMETER_CAMERA_CUSTOM_SENSOR_CONFIG, state->common_settings.sensor_mode);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("Could not set sensor mode : error %d", status);
      goto error;
   }

   preview_port = camera->output[MMAL_CAMERA_PREVIEW_PORT];
   video_port = camera->output[MMAL_CAMERA_VIDEO_PORT];
   still_port = camera->output[MMAL_CAMERA_CAPTURE_PORT];

   // Enable the camera, and tell it its control callback function
   status = mmal_port_enable(camera->control, default_camera_control_callback);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("Unable to enable control port : error %d", status);
      goto error;
   }

   //  set up the camera configuration
   {
      MMAL_PARAMETER_CAMERA_CONFIG_T cam_config =
      {
         { MMAL_PARAMETER_CAMERA_CONFIG, sizeof(cam_config) },
         .max_stills_w = state->common_settings.width,
         .max_stills_h = state->common_settings.height,
         .stills_yuv422 = 0,
         .one_shot_stills = 1,
         .max_preview_video_w = state->preview_parameters.previewWindow.width,
         .max_preview_video_h = state->preview_parameters.previewWindow.height,
         .num_preview_video_frames = 3,
         .stills_capture_circular_buffer_height = 0,
         .fast_preview_resume = 0,
         .use_stc_timestamp = MMAL_PARAM_TIMESTAMP_MODE_RESET_STC
      };

      if (state->fullResPreview)
      {
         cam_config.max_preview_video_w = state->common_settings.width;
         cam_config.max_preview_video_h = state->common_settings.height;
      }

      mmal_port_parameter_set(camera->control, &cam_config.hdr);
   }

   raspicamcontrol_set_all_parameters(camera, &state->camera_parameters);

   // Now set up the port formats

   format = preview_port->format;
   format->encoding = MMAL_ENCODING_OPAQUE;
   format->encoding_variant = MMAL_ENCODING_I420;

   if(state->camera_parameters.shutter_speed > 6000000)
   {
      MMAL_PARAMETER_FPS_RANGE_T fps_range = {{MMAL_PARAMETER_FPS_RANGE, sizeof(fps_range)},
         { 50, 1000 }, {166, 1000}
      };
      mmal_port_parameter_set(preview_port, &fps_range.hdr);
   }
   else if(state->camera_parameters.shutter_speed > 1000000)
   {
      MMAL_PARAMETER_FPS_RANGE_T fps_range = {{MMAL_PARAMETER_FPS_RANGE, sizeof(fps_range)},
         { 166, 1000 }, {999, 1000}
      };
      mmal_port_parameter_set(preview_port, &fps_range.hdr);
   }
   if (state->fullResPreview)
   {
      // In this mode we are forcing the preview to be generated from the full capture resolution.
      // This runs at a max of 15fps with the OV5647 sensor.
      format->es->video.width = VCOS_ALIGN_UP(state->common_settings.width, 32);
      format->es->video.height = VCOS_ALIGN_UP(state->common_settings.height, 16);
      format->es->video.crop.x = 0;
      format->es->video.crop.y = 0;
      format->es->video.crop.width = state->common_settings.width;
      format->es->video.crop.height = state->common_settings.height;
      format->es->video.frame_rate.num = FULL_RES_PREVIEW_FRAME_RATE_NUM;
      format->es->video.frame_rate.den = FULL_RES_PREVIEW_FRAME_RATE_DEN;
   }
   else
   {
      // Use a full FOV 4:3 mode
      format->es->video.width = VCOS_ALIGN_UP(state->preview_parameters.previewWindow.width, 32);
      format->es->video.height = VCOS_ALIGN_UP(state->preview_parameters.previewWindow.height, 16);
      format->es->video.crop.x = 0;
      format->es->video.crop.y = 0;
      format->es->video.crop.width = state->preview_parameters.previewWindow.width;
      format->es->video.crop.height = state->preview_parameters.previewWindow.height;
      format->es->video.frame_rate.num = PREVIEW_FRAME_RATE_NUM;
      format->es->video.frame_rate.den = PREVIEW_FRAME_RATE_DEN;
   }

   status = mmal_port_format_commit(preview_port);
   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("camera viewfinder format couldn't be set");
      goto error;
   }

   // Set the same format on the video  port (which we don't use here)
   mmal_format_full_copy(video_port->format, format);
   status = mmal_port_format_commit(video_port);

   if (status  != MMAL_SUCCESS)
   {
      vcos_log_error("camera video format couldn't be set");
      goto error;
   }

   // Ensure there are enough buffers to avoid dropping frames
   if (video_port->buffer_num < VIDEO_OUTPUT_BUFFERS_NUM)
      video_port->buffer_num = VIDEO_OUTPUT_BUFFERS_NUM;

   format = still_port->format;

   if(state->camera_parameters.shutter_speed > 6000000)
   {
      MMAL_PARAMETER_FPS_RANGE_T fps_range = {{MMAL_PARAMETER_FPS_RANGE, sizeof(fps_range)},
         { 50, 1000 }, {166, 1000}
      };
      mmal_port_parameter_set(still_port, &fps_range.hdr);
   }
   else if(state->camera_parameters.shutter_speed > 1000000)
   {
      MMAL_PARAMETER_FPS_RANGE_T fps_range = {{MMAL_PARAMETER_FPS_RANGE, sizeof(fps_range)},
         { 167, 1000 }, {999, 1000}
      };
      mmal_port_parameter_set(still_port, &fps_range.hdr);
   }
   // Set our stills format on the stills (for encoder) port
   format->encoding = MMAL_ENCODING_OPAQUE;
   format->es->video.width = VCOS_ALIGN_UP(state->common_settings.width, 32);
   format->es->video.height = VCOS_ALIGN_UP(state->common_settings.height, 16);
   format->es->video.crop.x = 0;
   format->es->video.crop.y = 0;
   format->es->video.crop.width = state->common_settings.width;
   format->es->video.crop.height = state->common_settings.height;
   format->es->video.frame_rate.num = STILLS_FRAME_RATE_NUM;
   format->es->video.frame_rate.den = STILLS_FRAME_RATE_DEN;

   status = mmal_port_format_commit(still_port);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("camera still format couldn't be set");
      goto error;
   }

   /* Ensure there are enough buffers to avoid dropping frames */
   if (still_port->buffer_num < VIDEO_OUTPUT_BUFFERS_NUM)
      still_port->buffer_num = VIDEO_OUTPUT_BUFFERS_NUM;

   /* Enable component */
   status = mmal_component_enable(camera);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("camera component couldn't be enabled");
      goto error;
   }

   if (state->useGL)
   {
      status = raspitex_configure_preview_port(&state->raspitex_state, preview_port);
      if (status != MMAL_SUCCESS)
      {
         fprintf(stderr, "Failed to configure preview port for GL rendering");
         goto error;
      }
   }

   state->camera_component = camera;

   if (state->common_settings.verbose)
      fprintf(stderr, "Camera component done\n");

   return status;

error:

   if (camera)
      mmal_component_destroy(camera);

   return status;
}
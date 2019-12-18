#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_18__ ;
typedef  struct TYPE_36__   TYPE_17__ ;
typedef  struct TYPE_35__   TYPE_16__ ;
typedef  struct TYPE_34__   TYPE_15__ ;
typedef  struct TYPE_33__   TYPE_14__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  camera_num ;
typedef  int /*<<< orphan*/  cam_config ;
struct TYPE_46__ {int den; } ;
struct TYPE_43__ {void* height; void* width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_44__ {TYPE_9__ frame_rate; TYPE_6__ crop; void* height; void* width; } ;
struct TYPE_45__ {TYPE_7__ video; } ;
struct TYPE_42__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_41__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_40__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_39__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_38__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_37__ {scalar_t__ change; TYPE_9__ frame_rate; scalar_t__ opaque; int /*<<< orphan*/  vformat; int /*<<< orphan*/  camera_num; } ;
struct TYPE_36__ {TYPE_10__* control; TYPE_10__** output; int /*<<< orphan*/  output_num; } ;
struct TYPE_35__ {TYPE_8__* es; int /*<<< orphan*/  encoding; } ;
struct TYPE_34__ {int member_2; int /*<<< orphan*/  hdr; int /*<<< orphan*/  member_1; TYPE_4__ member_0; } ;
struct TYPE_33__ {int member_1; int /*<<< orphan*/  hdr; TYPE_3__ member_0; } ;
struct TYPE_32__ {void* max_stills_w; void* max_stills_h; void* max_preview_video_w; void* max_preview_video_h; int num_preview_video_frames; int /*<<< orphan*/  hdr; int /*<<< orphan*/  use_stc_timestamp; int /*<<< orphan*/  fast_preview_resume; int /*<<< orphan*/  stills_capture_circular_buffer_height; int /*<<< orphan*/  one_shot_stills; int /*<<< orphan*/  stills_yuv422; TYPE_5__ member_0; } ;
struct TYPE_31__ {int member_2; int /*<<< orphan*/  hdr; int /*<<< orphan*/  change_id; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct TYPE_30__ {int /*<<< orphan*/  hdr; int /*<<< orphan*/  value; int /*<<< orphan*/  member_1; TYPE_2__ member_0; } ;
struct TYPE_29__ {scalar_t__ buffer_num; TYPE_16__* format; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_10__ MMAL_PORT_T ;
typedef  TYPE_11__ MMAL_PARAMETER_INT32_T ;
typedef  TYPE_12__ MMAL_PARAMETER_CHANGE_EVENT_REQUEST_T ;
typedef  TYPE_13__ MMAL_PARAMETER_CAMERA_CONFIG_T ;
typedef  TYPE_14__ MMAL_PARAMETER_BOOLEAN_T ;
typedef  TYPE_15__ MMAL_PARAMETER_ALGORITHM_CONTROL_T ;
typedef  TYPE_16__ MMAL_ES_FORMAT_T ;
typedef  TYPE_17__ MMAL_COMPONENT_T ;
typedef  TYPE_18__ MMALCAM_BEHAVIOUR_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int /*<<< orphan*/  LOG_INFO (char*) ; 
 scalar_t__ MMALCAM_CHANGE_HDR ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CAMERA ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENCODING_I420 ; 
 int /*<<< orphan*/  MMAL_ENCODING_OPAQUE ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ALGORITHM_CONTROL ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ALGORITHM_CONTROL_ALGORITHMS_HIGH_DYNAMIC_RANGE ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_CONFIG ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_NUM ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CHANGE_EVENT_REQUEST ; 
 int /*<<< orphan*/  MMAL_PARAMETER_FOCUS_STATUS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ZERO_COPY ; 
 int /*<<< orphan*/  MMAL_PARAM_TIMESTAMP_MODE_RESET_STC ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ VIDEO_OUTPUT_BUFFERS_NUM ; 
 int /*<<< orphan*/  control_bh_cb ; 
 scalar_t__ enable_zero_copy () ; 
 int /*<<< orphan*/  mmal_component_create (int /*<<< orphan*/ ,TYPE_17__**) ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_17__*) ; 
 int /*<<< orphan*/  mmal_component_enable (TYPE_17__*) ; 
 int /*<<< orphan*/  mmal_format_full_copy (TYPE_16__*,TYPE_16__*) ; 
 int /*<<< orphan*/  mmal_port_enable (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_format_commit (TYPE_10__*) ; 
 int /*<<< orphan*/  mmal_port_parameter_set (TYPE_10__*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_vformat (int /*<<< orphan*/ ,void**,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_COMPONENT_T *test_camera_create(MMALCAM_BEHAVIOUR_T *behaviour, MMAL_STATUS_T *status)
{
   MMAL_COMPONENT_T *camera = 0;
   MMAL_ES_FORMAT_T *format;
   MMAL_PARAMETER_CHANGE_EVENT_REQUEST_T change_event_request =
         {{MMAL_PARAMETER_CHANGE_EVENT_REQUEST, sizeof(MMAL_PARAMETER_CHANGE_EVENT_REQUEST_T)}, 0, 1};
   MMAL_PORT_T *viewfinder_port = NULL, *video_port = NULL, *still_port = NULL;
   uint32_t width, height;
   MMAL_PARAMETER_INT32_T camera_num =
         {{MMAL_PARAMETER_CAMERA_NUM, sizeof(camera_num)},0};

   /* Create the component */
   *status = mmal_component_create(MMAL_COMPONENT_DEFAULT_CAMERA, &camera);
   if(*status != MMAL_SUCCESS)
   {
      LOG_ERROR("couldn't create camera");
      goto error;
   }
   if(!camera->output_num)
   {
      LOG_ERROR("camera doesn't have output ports");
      *status = MMAL_EINVAL;
      goto error;
   }

   viewfinder_port = camera->output[0];
   video_port = camera->output[1];
   still_port = camera->output[2];

   change_event_request.change_id = MMAL_PARAMETER_FOCUS_STATUS;
   *status = mmal_port_parameter_set(camera->control, &change_event_request.hdr);
   if (*status != MMAL_SUCCESS && *status != MMAL_ENOSYS)
   {
      LOG_ERROR("No focus status change events");
   }
   camera_num.value = behaviour->camera_num;
   *status = mmal_port_parameter_set(camera->control, &camera_num.hdr);
   if (*status != MMAL_SUCCESS && *status != MMAL_ENOSYS)
   {
       LOG_ERROR("No camera number change events");
   }
   if (enable_zero_copy())
   {
      MMAL_PARAMETER_BOOLEAN_T param_zc =
         {{MMAL_PARAMETER_ZERO_COPY, sizeof(MMAL_PARAMETER_BOOLEAN_T)}, 1};
      *status = mmal_port_parameter_set(viewfinder_port, &param_zc.hdr);
      if( *status != MMAL_SUCCESS && *status != MMAL_ENOSYS )
      {
         LOG_ERROR("failed to set zero copy on camera output");
         goto error;
      }
      LOG_INFO("enabled zero copy on camera");
      *status = mmal_port_parameter_set(video_port, &param_zc.hdr);
      if( *status != MMAL_SUCCESS && *status != MMAL_ENOSYS )
      {
         LOG_ERROR("failed to set zero copy on camera output");
         goto error;
      }
      *status = mmal_port_parameter_set(still_port, &param_zc.hdr);
      if( *status != MMAL_SUCCESS && *status != MMAL_ENOSYS )
      {
         LOG_ERROR("failed to set zero copy on camera output");
         goto error;
      }
   }

   if ( behaviour->change == MMALCAM_CHANGE_HDR )
   {
      MMAL_PARAMETER_ALGORITHM_CONTROL_T algo_ctrl = {{MMAL_PARAMETER_ALGORITHM_CONTROL, sizeof(MMAL_PARAMETER_ALGORITHM_CONTROL_T)},
                        MMAL_PARAMETER_ALGORITHM_CONTROL_ALGORITHMS_HIGH_DYNAMIC_RANGE, 1 };
      mmal_port_parameter_set(camera->control, &algo_ctrl.hdr);
   }

   *status = mmal_port_enable(camera->control, control_bh_cb);
   if (*status)
   {
      LOG_ERROR("control port couldn't be enabled: %d", *status);
      goto error;
   }

   /* Set camera viewfinder port format */
   if (parse_vformat(behaviour->vformat, &width, &height, NULL))
   {
      *status = MMAL_EINVAL;
      goto error;
   }

   /* Default to integer frame rate in numerator */
   if (!behaviour->frame_rate.den)
      behaviour->frame_rate.den = 1;

   {
      MMAL_PARAMETER_CAMERA_CONFIG_T cam_config = {{MMAL_PARAMETER_CAMERA_CONFIG,sizeof(cam_config)},
                              .max_stills_w =      width,
                              .max_stills_h =      height,
                              .stills_yuv422 =     0,
                              .one_shot_stills =   0,
                              .max_preview_video_w = width,
                              .max_preview_video_h = height,
                              .num_preview_video_frames = 3,
                              .stills_capture_circular_buffer_height = 0,
                              .fast_preview_resume = 0,
                                          /* No way of using fast resume in Android, as preview
                                           * automatically stops on capture.
                                           */
                              .use_stc_timestamp = MMAL_PARAM_TIMESTAMP_MODE_RESET_STC
                              };

      mmal_port_parameter_set(camera->control, &cam_config.hdr);
   }

   /* Set up the viewfinder port format */
   format = viewfinder_port->format;
   if (behaviour->opaque)
      format->encoding = MMAL_ENCODING_OPAQUE;
   else
      format->encoding = MMAL_ENCODING_I420;

   format->es->video.width = width;
   format->es->video.height = height;
   format->es->video.crop.x = 0;
   format->es->video.crop.y = 0;
   format->es->video.crop.width = width;
   format->es->video.crop.height = height;
   format->es->video.frame_rate = behaviour->frame_rate;

   *status = mmal_port_format_commit(viewfinder_port);
   if(*status)
   {
      LOG_ERROR("camera viewfinder format couldn't be set");
      goto error;
   }

   /* Set the same format on the video (for encoder) port */
   mmal_format_full_copy(video_port->format, format);
   *status = mmal_port_format_commit(video_port);
   if(*status)
   {
      LOG_ERROR("camera video format couldn't be set");
      goto error;
   }

   /* Ensure there are enough buffers to avoid dropping frames */
   if (video_port->buffer_num < VIDEO_OUTPUT_BUFFERS_NUM)
      video_port->buffer_num = VIDEO_OUTPUT_BUFFERS_NUM;

   /* Set the same format on the still (for encoder) port */
   mmal_format_full_copy(still_port->format, format);
   *status = mmal_port_format_commit(still_port);
   if(*status)
   {
      LOG_ERROR("camera still format couldn't be set");
      goto error;
   }

   /* Ensure there are enough buffers to avoid dropping frames */
   if (still_port->buffer_num < VIDEO_OUTPUT_BUFFERS_NUM)
      still_port->buffer_num = VIDEO_OUTPUT_BUFFERS_NUM;

   /* Enable component */
   *status = mmal_component_enable(camera);
   if(*status)
   {
      LOG_ERROR("camera component couldn't be enabled");
      goto error;
   }

   return camera;

 error:
   if(camera) mmal_component_destroy(camera);
   return 0;
}
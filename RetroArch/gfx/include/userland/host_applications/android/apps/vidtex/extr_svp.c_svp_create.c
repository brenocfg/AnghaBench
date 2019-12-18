#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_32__ {int /*<<< orphan*/ * input; TYPE_8__** output; int /*<<< orphan*/  control; } ;
struct TYPE_31__ {int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer_num; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_num_recommended; TYPE_2__* format; } ;
struct TYPE_27__ {int den; int /*<<< orphan*/  num; } ;
struct TYPE_26__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_30__ {TYPE_4__ frame_rate; int /*<<< orphan*/  height; TYPE_3__ crop; int /*<<< orphan*/  width; } ;
struct TYPE_29__ {int /*<<< orphan*/  stop_cb; int /*<<< orphan*/  video_frame_cb; } ;
struct TYPE_28__ {TYPE_8__* video_output; int /*<<< orphan*/  queue; scalar_t__ out_pool; int /*<<< orphan*/ * connection; TYPE_9__* camera; TYPE_9__* video_decode; TYPE_9__* reader; int /*<<< orphan*/  created; int /*<<< orphan*/  wd_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  mutex; int /*<<< orphan*/  sema; TYPE_6__ callbacks; int /*<<< orphan*/  opts; } ;
struct TYPE_25__ {scalar_t__ type; TYPE_1__* es; int /*<<< orphan*/  encoding; } ;
struct TYPE_24__ {TYPE_7__ video; } ;
typedef  TYPE_5__ SVP_T ;
typedef  int /*<<< orphan*/  SVP_OPTS_T ;
typedef  TYPE_6__ SVP_CALLBACKS_T ;
typedef  TYPE_7__ MMAL_VIDEO_FORMAT_T ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_8__ MMAL_PORT_T ;
typedef  TYPE_9__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STATUS (scalar_t__,char*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,char const*) ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CAMERA ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CONTAINER_READER ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_DECODER ; 
 int /*<<< orphan*/  MMAL_CONNECTION_FLAG_TUNNELLING ; 
 scalar_t__ MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENCODING_OPAQUE ; 
 scalar_t__ MMAL_ENOMEM ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ZERO_COPY ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  SVP_CAMERA_FRAMERATE ; 
 int /*<<< orphan*/  SVP_CAMERA_HEIGHT ; 
 int /*<<< orphan*/  SVP_CAMERA_WIDTH ; 
 int /*<<< orphan*/  SVP_CREATED_MUTEX ; 
 int /*<<< orphan*/  SVP_CREATED_SEM ; 
 int /*<<< orphan*/  SVP_CREATED_TIMER ; 
 int /*<<< orphan*/  SVP_CREATED_WD_TIMER ; 
 scalar_t__ VCOS_SUCCESS ; 
 scalar_t__ mmal_component_create (int /*<<< orphan*/ ,TYPE_9__**) ; 
 scalar_t__ mmal_component_enable (TYPE_9__*) ; 
 scalar_t__ mmal_connection_create (int /*<<< orphan*/ **,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_format_commit (TYPE_8__*) ; 
 scalar_t__ mmal_port_parameter_set_boolean (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_pool_create (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_create () ; 
 int /*<<< orphan*/  svp_bh_control_cb ; 
 int /*<<< orphan*/  svp_destroy (TYPE_5__*) ; 
 scalar_t__ svp_port_enable (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svp_setup_reader (TYPE_9__*,char const*,TYPE_8__**) ; 
 int /*<<< orphan*/  svp_timer_cb ; 
 int /*<<< orphan*/  svp_watchdog_cb ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 TYPE_5__* vcos_calloc (int,int,char*) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vcos_semaphore_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_timer_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_5__*) ; 

SVP_T *svp_create(const char *uri, SVP_CALLBACKS_T *callbacks, const SVP_OPTS_T *opts)
{
   SVP_T *svp;
   MMAL_STATUS_T st;
   VCOS_STATUS_T vst;
   MMAL_PORT_T *reader_output = NULL;
   MMAL_COMPONENT_T *video_decode = NULL;
   MMAL_PORT_T *video_output = NULL;

   LOG_TRACE("Creating player for %s", (uri ? uri : "camera preview"));

   vcos_assert(callbacks->video_frame_cb);
   vcos_assert(callbacks->stop_cb);

   svp = vcos_calloc(1, sizeof(*svp), "svp");
   CHECK_STATUS((svp ? MMAL_SUCCESS : MMAL_ENOMEM), "Failed to allocate context");

   svp->opts = *opts;
   svp->callbacks = *callbacks;

   /* Semaphore used for synchronising buffer handling for decoded frames */
   vst = vcos_semaphore_create(&svp->sema, "svp-sem", 0);
   CHECK_STATUS((vst == VCOS_SUCCESS ? MMAL_SUCCESS : MMAL_ENOMEM), "Failed to create semaphore");
   svp->created |= SVP_CREATED_SEM;

   vst = vcos_mutex_create(&svp->mutex, "svp-mutex");
   CHECK_STATUS((vst == VCOS_SUCCESS ? MMAL_SUCCESS : MMAL_ENOMEM), "Failed to create mutex");
   svp->created |= SVP_CREATED_MUTEX;

   vst = vcos_timer_create(&svp->timer, "svp-timer", svp_timer_cb, svp);
   CHECK_STATUS((vst == VCOS_SUCCESS ? MMAL_SUCCESS : MMAL_ENOMEM), "Failed to create timer");
   svp->created |= SVP_CREATED_TIMER;

   vst = vcos_timer_create(&svp->wd_timer, "svp-wd-timer", svp_watchdog_cb, svp);
   CHECK_STATUS((vst == VCOS_SUCCESS ? MMAL_SUCCESS : MMAL_ENOMEM), "Failed to create timer");
   svp->created |= SVP_CREATED_WD_TIMER;

   /* Create components */
   svp->reader = NULL;
   svp->video_decode = NULL;
   svp->camera = NULL;
   svp->connection = NULL;

   if (uri)
   {
      /* Video from URI: setup container_reader -> video_decode */

      /* Create and set up container reader */
      st = mmal_component_create(MMAL_COMPONENT_DEFAULT_CONTAINER_READER, &svp->reader);
      CHECK_STATUS(st, "Failed to create container reader");

      st = svp_setup_reader(svp->reader, uri, &reader_output);
      if (st != MMAL_SUCCESS)
         goto error;

      st = mmal_component_enable(svp->reader);
      CHECK_STATUS(st, "Failed to enable container reader");

      st = svp_port_enable(svp, svp->reader->control, svp_bh_control_cb);
      CHECK_STATUS(st, "Failed to enable container reader control port");

      /* Create and set up video decoder */
      st = mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_DECODER, &svp->video_decode);
      CHECK_STATUS(st, "Failed to create video decoder");

      video_decode = svp->video_decode;
      video_output = video_decode->output[0];

      st = mmal_component_enable(video_decode);
      CHECK_STATUS(st, "Failed to enable video decoder");

      st = svp_port_enable(svp, video_decode->control, svp_bh_control_cb);
      CHECK_STATUS(st, "Failed to enable video decoder control port");
   }
   else
   {
      /* Camera preview */
      st = mmal_component_create(MMAL_COMPONENT_DEFAULT_CAMERA, &svp->camera);
      CHECK_STATUS(st, "Failed to create camera");

      st = mmal_component_enable(svp->camera);
      CHECK_STATUS(st, "Failed to enable camera");

      st = svp_port_enable(svp, svp->camera->control, svp_bh_control_cb);
      CHECK_STATUS(st, "Failed to enable camera control port");

      video_output = svp->camera->output[0]; /* Preview port */
   }

   st = mmal_port_parameter_set_boolean(video_output, MMAL_PARAMETER_ZERO_COPY, MMAL_TRUE);
   CHECK_STATUS((st == MMAL_ENOSYS ? MMAL_SUCCESS : st), "Failed to enable zero copy");

   if (uri)
   {
      /* Create connection: container_reader -> video_decoder */
      st = mmal_connection_create(&svp->connection, reader_output, video_decode->input[0],
                                  MMAL_CONNECTION_FLAG_TUNNELLING);
      CHECK_STATUS(st, "Failed to create connection");
   }

   /* Set video output port format.
    * Opaque encoding ensures we get buffer data as handles to relocatable heap. */
   video_output->format->encoding = MMAL_ENCODING_OPAQUE;

   if (!uri)
   {
      /* Set video format for camera preview */
      MMAL_VIDEO_FORMAT_T *vfmt = &video_output->format->es->video;

      CHECK_STATUS((video_output->format->type == MMAL_ES_TYPE_VIDEO) ? MMAL_SUCCESS : MMAL_EINVAL,
                   "Output port isn't video format");

      vfmt->width = SVP_CAMERA_WIDTH;
      vfmt->height = SVP_CAMERA_HEIGHT;
      vfmt->crop.x = 0;
      vfmt->crop.y = 0;
      vfmt->crop.width = vfmt->width;
      vfmt->crop.height = vfmt->height;
      vfmt->frame_rate.num = SVP_CAMERA_FRAMERATE;
      vfmt->frame_rate.den = 1;
   }

   st = mmal_port_format_commit(video_output);
   CHECK_STATUS(st, "Failed to set output port format");

   /* Finally, set buffer num/size. N.B. For container_reader/video_decode, must be after
    * connection created, in order for port format to propagate.
    * Don't enable video output port until want to produce frames. */
   video_output->buffer_num = video_output->buffer_num_recommended;
   video_output->buffer_size = video_output->buffer_size_recommended;

   /* Pool + queue to hold decoded video frames */
   svp->out_pool = mmal_port_pool_create(video_output, video_output->buffer_num,
                                         video_output->buffer_size);
   CHECK_STATUS((svp->out_pool ? MMAL_SUCCESS : MMAL_ENOMEM), "Error allocating pool");
   svp->queue = mmal_queue_create();
   CHECK_STATUS((svp ? MMAL_SUCCESS : MMAL_ENOMEM), "Error allocating queue");

   svp->video_output = video_output;

   return svp;

error:
   svp_destroy(svp);
   return NULL;
}
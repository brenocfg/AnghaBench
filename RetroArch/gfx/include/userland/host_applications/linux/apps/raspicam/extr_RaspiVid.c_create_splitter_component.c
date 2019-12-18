#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_5__* format; } ;
struct TYPE_21__ {int output_num; TYPE_4__** output; TYPE_4__** input; int /*<<< orphan*/  input_num; } ;
struct TYPE_20__ {void* encoding_variant; void* encoding; } ;
struct TYPE_19__ {scalar_t__ buffer_num; int name; int /*<<< orphan*/  buffer_size; TYPE_5__* format; } ;
struct TYPE_17__ {scalar_t__ verbose; } ;
struct TYPE_18__ {int raw_output_fmt; TYPE_2__ common_settings; TYPE_6__* splitter_component; int /*<<< orphan*/ * splitter_pool; TYPE_1__* camera_component; } ;
struct TYPE_16__ {TYPE_7__** output; } ;
typedef  TYPE_3__ RASPIVID_STATE ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_4__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;
typedef  TYPE_5__ MMAL_ES_FORMAT_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;

/* Variables and functions */
 size_t MMAL_CAMERA_CAPTURE_PORT ; 
 size_t MMAL_CAMERA_PREVIEW_PORT ; 
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_VIDEO_SPLITTER ; 
 scalar_t__ MMAL_EINVAL ; 
 void* MMAL_ENCODING_BGR24 ; 
 void* MMAL_ENCODING_I420 ; 
 void* MMAL_ENCODING_RGB24 ; 
 scalar_t__ MMAL_ENOSYS ; 
 scalar_t__ MMAL_SUCCESS ; 
#define  RAW_OUTPUT_FMT_GRAY 130 
#define  RAW_OUTPUT_FMT_RGB 129 
#define  RAW_OUTPUT_FMT_YUV 128 
 int SPLITTER_OUTPUT_PORT ; 
 scalar_t__ VIDEO_OUTPUT_BUFFERS_NUM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mmal_component_create (int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_6__*) ; 
 scalar_t__ mmal_component_enable (TYPE_6__*) ; 
 int /*<<< orphan*/  mmal_format_copy (TYPE_5__*,TYPE_5__*) ; 
 scalar_t__ mmal_port_format_commit (TYPE_4__*) ; 
 int /*<<< orphan*/ * mmal_port_pool_create (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_util_rgb_order_fixed (TYPE_7__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vcos_log_error (char*,...) ; 

__attribute__((used)) static MMAL_STATUS_T create_splitter_component(RASPIVID_STATE *state)
{
   MMAL_COMPONENT_T *splitter = 0;
   MMAL_PORT_T *splitter_output = NULL;
   MMAL_ES_FORMAT_T *format;
   MMAL_STATUS_T status;
   MMAL_POOL_T *pool;
   int i;

   if (state->camera_component == NULL)
   {
      status = MMAL_ENOSYS;
      vcos_log_error("Camera component must be created before splitter");
      goto error;
   }

   /* Create the component */
   status = mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_SPLITTER, &splitter);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("Failed to create splitter component");
      goto error;
   }

   if (!splitter->input_num)
   {
      status = MMAL_ENOSYS;
      vcos_log_error("Splitter doesn't have any input port");
      goto error;
   }

   if (splitter->output_num < 2)
   {
      status = MMAL_ENOSYS;
      vcos_log_error("Splitter doesn't have enough output ports");
      goto error;
   }

   /* Ensure there are enough buffers to avoid dropping frames: */
   mmal_format_copy(splitter->input[0]->format, state->camera_component->output[MMAL_CAMERA_PREVIEW_PORT]->format);

   if (splitter->input[0]->buffer_num < VIDEO_OUTPUT_BUFFERS_NUM)
      splitter->input[0]->buffer_num = VIDEO_OUTPUT_BUFFERS_NUM;

   status = mmal_port_format_commit(splitter->input[0]);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("Unable to set format on splitter input port");
      goto error;
   }

   /* Splitter can do format conversions, configure format for its output port: */
   for (i = 0; i < splitter->output_num; i++)
   {
      mmal_format_copy(splitter->output[i]->format, splitter->input[0]->format);

      if (i == SPLITTER_OUTPUT_PORT)
      {
         format = splitter->output[i]->format;

         switch (state->raw_output_fmt)
         {
         case RAW_OUTPUT_FMT_YUV:
         case RAW_OUTPUT_FMT_GRAY: /* Grayscale image contains only luma (Y) component */
            format->encoding = MMAL_ENCODING_I420;
            format->encoding_variant = MMAL_ENCODING_I420;
            break;
         case RAW_OUTPUT_FMT_RGB:
            if (mmal_util_rgb_order_fixed(state->camera_component->output[MMAL_CAMERA_CAPTURE_PORT]))
               format->encoding = MMAL_ENCODING_RGB24;
            else
               format->encoding = MMAL_ENCODING_BGR24;
            format->encoding_variant = 0;  /* Irrelevant when not in opaque mode */
            break;
         default:
            status = MMAL_EINVAL;
            vcos_log_error("unknown raw output format");
            goto error;
         }
      }

      status = mmal_port_format_commit(splitter->output[i]);

      if (status != MMAL_SUCCESS)
      {
         vcos_log_error("Unable to set format on splitter output port %d", i);
         goto error;
      }
   }

   /* Enable component */
   status = mmal_component_enable(splitter);

   if (status != MMAL_SUCCESS)
   {
      vcos_log_error("splitter component couldn't be enabled");
      goto error;
   }

   /* Create pool of buffer headers for the output port to consume */
   splitter_output = splitter->output[SPLITTER_OUTPUT_PORT];
   pool = mmal_port_pool_create(splitter_output, splitter_output->buffer_num, splitter_output->buffer_size);

   if (!pool)
   {
      vcos_log_error("Failed to create buffer header pool for splitter output port %s", splitter_output->name);
   }

   state->splitter_pool = pool;
   state->splitter_component = splitter;

   if (state->common_settings.verbose)
      fprintf(stderr, "Splitter component done\n");

   return status;

error:

   if (splitter)
      mmal_component_destroy(splitter);

   return status;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_20__ {scalar_t__ opaque; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  vformat; } ;
struct TYPE_19__ {TYPE_2__** output; TYPE_2__** input; int /*<<< orphan*/  output_num; int /*<<< orphan*/  input_num; } ;
struct TYPE_16__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {int member_1; int /*<<< orphan*/  hdr; TYPE_1__ member_0; } ;
struct TYPE_17__ {scalar_t__ buffer_size; scalar_t__ buffer_size_recommended; scalar_t__ buffer_size_min; scalar_t__ buffer_num; scalar_t__ buffer_num_recommended; scalar_t__ buffer_num_min; TYPE_10__* format; } ;
struct TYPE_15__ {scalar_t__ encoding; int /*<<< orphan*/  bitrate; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PORT_T ;
typedef  TYPE_3__ MMAL_PARAMETER_BOOLEAN_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  TYPE_5__ MMALCAM_BEHAVIOUR_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  LOG_INFO (char*) ; 
 char* MMAL_COMPONENT_DEFAULT_IMAGE_ENCODER ; 
 char* MMAL_COMPONENT_DEFAULT_VIDEO_ENCODER ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 scalar_t__ MMAL_ENCODING_JPEG ; 
 scalar_t__ MMAL_ENCODING_OPAQUE ; 
 int /*<<< orphan*/  MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ZERO_COPY ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ enable_zero_copy () ; 
 int /*<<< orphan*/  mmal_component_create (char const*,TYPE_4__**) ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_component_enable (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_format_copy (TYPE_10__*,TYPE_10__*) ; 
 int /*<<< orphan*/  mmal_port_format_commit (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_port_parameter_set (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_vformat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static MMAL_COMPONENT_T *test_video_encoder_create(MMALCAM_BEHAVIOUR_T *behaviour, MMAL_STATUS_T *status)
{
   MMAL_COMPONENT_T *encoder = 0;
   MMAL_PORT_T *encoder_input = NULL, *encoder_output = NULL;
   const char *component_name = MMAL_COMPONENT_DEFAULT_VIDEO_ENCODER;
   uint32_t encoding;

   /* Set the port format */
   if (parse_vformat(behaviour->vformat, 0, 0, &encoding))
   {
      *status = MMAL_EINVAL;
      goto error;
   }

   if (encoding == MMAL_ENCODING_JPEG)
      component_name = MMAL_COMPONENT_DEFAULT_IMAGE_ENCODER;

   *status = mmal_component_create(component_name, &encoder);
   if(*status != MMAL_SUCCESS)
   {
      LOG_ERROR("couldn't create video encoder");
      goto error;
   }
   if(!encoder->input_num || !encoder->output_num)
   {
      LOG_ERROR("video encoder doesn't have input/output ports");
      *status = MMAL_EINVAL;
      goto error;
   }

   encoder_input = encoder->input[0];
   encoder_output = encoder->output[0];

   mmal_format_copy(encoder_output->format, encoder_input->format);
   encoder_output->format->encoding = encoding;
   encoder_output->format->bitrate = behaviour->bit_rate;
   *status = mmal_port_format_commit(encoder_output);
   if(*status != MMAL_SUCCESS)
   {
      LOG_ERROR("format not set on video encoder output port");
      goto error;
   }
   encoder_output->buffer_size = encoder_output->buffer_size_recommended;
   if (encoder_output->buffer_size < encoder_output->buffer_size_min)
      encoder_output->buffer_size = encoder_output->buffer_size_min;
   encoder_output->buffer_num = encoder_output->buffer_num_recommended;
   if (encoder_output->buffer_num < encoder_output->buffer_num_min)
      encoder_output->buffer_num = encoder_output->buffer_num_min;

   if (enable_zero_copy())
   {
      MMAL_PARAMETER_BOOLEAN_T param_zc =
         {{MMAL_PARAMETER_ZERO_COPY, sizeof(MMAL_PARAMETER_BOOLEAN_T)}, 1};
      *status = mmal_port_parameter_set(encoder_output, &param_zc.hdr);
      if (*status != MMAL_SUCCESS && *status != MMAL_ENOSYS)
      {
         LOG_ERROR("failed to set zero copy on encoder output");
         goto error;
      }
      *status = mmal_port_parameter_set(encoder_input, &param_zc.hdr);
      if (*status != MMAL_SUCCESS && *status != MMAL_ENOSYS)
      {
         LOG_ERROR("failed to set zero copy on encoder input");
         goto error;
      }
      LOG_INFO("enabled zero copy on encoder");
   }

   if (behaviour->opaque)
   {
      encoder_input->format->encoding = MMAL_ENCODING_OPAQUE;
   }

   /* Enable component */
   *status = mmal_component_enable(encoder);
   if(*status)
   {
      LOG_ERROR("video encoder component couldn't be enabled");
      goto error;
   }

   return encoder;

 error:
   if(encoder) mmal_component_destroy(encoder);
   return 0;
}
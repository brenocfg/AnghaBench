#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  copy_output; } ;
struct TYPE_13__ {TYPE_8__* converter_out_port; TYPE_2__ options; } ;
struct TYPE_12__ {TYPE_8__** output; TYPE_8__** input; int /*<<< orphan*/  name; int /*<<< orphan*/  output_num; int /*<<< orphan*/  input_num; } ;
struct TYPE_9__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int member_1; int /*<<< orphan*/  hdr; TYPE_1__ member_0; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PARAMETER_BOOLEAN_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  TYPE_5__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ZERO_COPY ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_port_parameter_set (TYPE_8__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmalplay_setup_video_converter(MMALPLAY_T *ctx, MMAL_COMPONENT_T *converter)
{
   MMAL_PARAMETER_BOOLEAN_T param_zc =
      {{MMAL_PARAMETER_ZERO_COPY, sizeof(MMAL_PARAMETER_BOOLEAN_T)}, 1};
   MMAL_STATUS_T status = MMAL_EINVAL;

   if(!converter->input_num || !converter->output_num)
   {
      LOG_ERROR("%s doesn't have input/output ports", converter->name);
      goto error;
   }

   /* Enable Zero Copy if requested. This needs to be sent before enabling the port. */
   if (!ctx->options.copy_output)
   {
      status = mmal_port_parameter_set(converter->input[0], &param_zc.hdr);
      if (status != MMAL_SUCCESS && status != MMAL_ENOSYS)
      {
         LOG_ERROR("failed to set zero copy on %s", converter->input[0]->name);
         goto error;
      }
      status = mmal_port_parameter_set(converter->output[0], &param_zc.hdr);
      if (status != MMAL_SUCCESS && status != MMAL_ENOSYS)
      {
         LOG_ERROR("failed to set zero copy on %s", converter->output[0]->name);
         goto error;
      }
   }

   ctx->converter_out_port = converter->output[0];
   status = MMAL_SUCCESS;

 error:
   return status;
}
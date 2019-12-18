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
struct TYPE_9__ {scalar_t__ output_num; int /*<<< orphan*/  copy_output; } ;
struct TYPE_13__ {TYPE_1__ options; } ;
struct TYPE_12__ {scalar_t__ output_num; TYPE_8__** output; TYPE_8__** input; int /*<<< orphan*/  name; int /*<<< orphan*/  input_num; } ;
struct TYPE_10__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int member_1; int /*<<< orphan*/  hdr; TYPE_2__ member_0; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PARAMETER_BOOLEAN_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;
typedef  TYPE_5__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ZERO_COPY ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_port_parameter_set (TYPE_8__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmalplay_setup_splitter(MMALPLAY_T *ctx, MMAL_COMPONENT_T *splitter)
{
   MMAL_STATUS_T status = MMAL_EINVAL;

   if(!splitter->input_num || !splitter->output_num)
   {
      LOG_ERROR("%s doesn't have input ports", splitter->name);
      goto error;
   }
   if(splitter->output_num < ctx->options.output_num)
   {
      LOG_ERROR("%s doesn't have enough output ports (%u/%u)", splitter->name,
                (unsigned int)splitter->output_num, ctx->options.output_num);
      goto error;
   }

   /* Enable Zero Copy if requested. This needs to be sent before enabling the port. */
   if (!ctx->options.copy_output)
   {
      MMAL_PARAMETER_BOOLEAN_T param_zc =
         {{MMAL_PARAMETER_ZERO_COPY, sizeof(MMAL_PARAMETER_BOOLEAN_T)}, 1};
      unsigned int i;

      status = mmal_port_parameter_set(splitter->input[0], &param_zc.hdr);
      if (status != MMAL_SUCCESS && status != MMAL_ENOSYS)
      {
         LOG_ERROR("failed to set zero copy on %s", splitter->input[0]->name);
         goto error;
      }
      for (i = 0; i < splitter->output_num; i++)
      {
         status = mmal_port_parameter_set(splitter->output[i], &param_zc.hdr);
         if (status != MMAL_SUCCESS && status != MMAL_ENOSYS)
         {
            LOG_ERROR("failed to set zero copy on %s", splitter->output[i]->name);
            goto error;
         }
      }
   }

   status = MMAL_SUCCESS;

 error:
   return status;
}
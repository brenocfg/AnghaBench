#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  copy_output; scalar_t__ audio_destination; } ;
struct TYPE_9__ {int /*<<< orphan*/  audio_clock; TYPE_1__ options; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * clock; scalar_t__ clock_num; TYPE_6__** input; int /*<<< orphan*/  control; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_INFO (char*) ; 
 scalar_t__ MMAL_EINVAL ; 
 scalar_t__ MMAL_ENOSYS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_AUDIO_DESTINATION ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ZERO_COPY ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 scalar_t__ mmal_port_parameter_set_boolean (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_parameter_set_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static MMAL_STATUS_T mmalplay_setup_audio_render(MMALPLAY_T *ctx, MMAL_COMPONENT_T *render)
{
   MMAL_STATUS_T status = MMAL_EINVAL;

   /* Set the audio destination - not all audio render components support this */
   if (ctx->options.audio_destination)
   {
      status = mmal_port_parameter_set_string(render->control,
            MMAL_PARAMETER_AUDIO_DESTINATION, ctx->options.audio_destination);
      if (status != MMAL_SUCCESS)
         LOG_INFO("could not set audio destination");
   }

   /* Enable Zero Copy if requested. This needs to be sent before enabling the port. */
   if (!ctx->options.copy_output)
   {
      status = mmal_port_parameter_set_boolean(render->input[0],
            MMAL_PARAMETER_ZERO_COPY, MMAL_TRUE);
      if (status != MMAL_SUCCESS && status != MMAL_ENOSYS)
      {
         LOG_ERROR("failed to set zero copy on %s", render->input[0]->name);
         goto error;
      }
   }

   if (render->clock_num)
      ctx->audio_clock = render->clock[0];
   else
      LOG_ERROR("%s doesn't have a clock port", render->name);

   status = MMAL_SUCCESS;

 error:
   return status;
}
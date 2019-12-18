#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ codec; TYPE_3__* extradata; } ;
struct TYPE_10__ {scalar_t__ queue_out; scalar_t__ queue_in; TYPE_6__* codec_context; TYPE_6__* picture; } ;
struct TYPE_9__ {int /*<<< orphan*/  output; scalar_t__ output_num; int /*<<< orphan*/  input; scalar_t__ input_num; TYPE_1__* priv; } ;
struct TYPE_8__ {TYPE_3__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_COMPONENT_T ;
typedef  TYPE_3__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  av_free (TYPE_6__*) ; 
 int /*<<< orphan*/  avcodec_close (TYPE_6__*) ; 
 int /*<<< orphan*/  mmal_ports_free (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmal_queue_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vcos_free (TYPE_3__*) ; 

__attribute__((used)) static MMAL_STATUS_T avcodec_component_destroy(MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;

   if (module->picture)
      av_free(module->picture);
   if (module->codec_context)
   {
      if(module->codec_context->extradata) vcos_free(module->codec_context->extradata);
      if(module->codec_context->codec) avcodec_close(module->codec_context);
      av_free(module->codec_context);
   }

   if(module->queue_in) mmal_queue_destroy(module->queue_in);
   if(module->queue_out) mmal_queue_destroy(module->queue_out);
   vcos_free(module);
   if(component->input_num) mmal_ports_free(component->input, 1);
   if(component->output_num) mmal_ports_free(component->output, 1);
   return MMAL_SUCCESS;
}
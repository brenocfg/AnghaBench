#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {int channels; int bits_per_sample; } ;
struct TYPE_28__ {TYPE_8__ audio; } ;
struct TYPE_26__ {int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; TYPE_6__* format; TYPE_3__* priv; } ;
struct TYPE_25__ {void* encoding; void* type; } ;
struct TYPE_24__ {TYPE_4__* module; int /*<<< orphan*/  pf_set_format; void* pf_send; void* pf_flush; void* pf_disable; void* pf_enable; } ;
struct TYPE_23__ {void* queue; } ;
struct TYPE_22__ {TYPE_2__* module; int /*<<< orphan*/  pf_set_format; void* pf_send; void* pf_flush; void* pf_disable; void* pf_enable; } ;
struct TYPE_21__ {void* queue; } ;
struct TYPE_20__ {int /*<<< orphan*/  (* pf_destroy ) (TYPE_12__*) ;int /*<<< orphan*/ * module; } ;
struct TYPE_19__ {int input_num; int output_num; TYPE_11__** output; TYPE_7__** input; TYPE_1__* priv; } ;
struct TYPE_18__ {int /*<<< orphan*/  buffer_num_recommended; int /*<<< orphan*/  buffer_num_min; int /*<<< orphan*/  buffer_size_recommended; int /*<<< orphan*/  buffer_size_min; TYPE_10__* format; TYPE_5__* priv; } ;
struct TYPE_17__ {TYPE_9__* es; void* encoding; void* type; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_MODULE_T ;
typedef  TYPE_12__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_MIN_BUFFER_NUM ; 
 int /*<<< orphan*/  INPUT_MIN_BUFFER_SIZE ; 
 void* MMAL_ENCODING_AC3 ; 
 scalar_t__ MMAL_ENOMEM ; 
 void* MMAL_ES_TYPE_AUDIO ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (char const*) ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_INPUT ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  OUTPUT_MIN_BUFFER_NUM ; 
 int /*<<< orphan*/  OUTPUT_MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmal_component_action_register (TYPE_12__*,int /*<<< orphan*/ ) ; 
 void* mmal_ports_alloc (TYPE_12__*,int,int /*<<< orphan*/ ,int) ; 
 void* mmal_queue_create () ; 
 int /*<<< orphan*/  spdif_component_destroy (TYPE_12__*) ; 
 int /*<<< orphan*/  spdif_do_processing_loop ; 
 int /*<<< orphan*/  spdif_input_port_format_commit ; 
 int /*<<< orphan*/  spdif_output_port_format_commit ; 
 void* spdif_port_disable ; 
 void* spdif_port_enable ; 
 void* spdif_port_flush ; 
 void* spdif_port_send ; 
 int /*<<< orphan*/ * vcos_malloc (int,char*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_component_create_spdif(const char *name, MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module;
   MMAL_STATUS_T status = MMAL_ENOMEM;
   MMAL_PARAM_UNUSED(name);

   /* Allocate the context for our module */
   component->priv->module = module = vcos_malloc(sizeof(*module), "mmal module");
   if (!module)
      return MMAL_ENOMEM;
   memset(module, 0, sizeof(*module));

   component->priv->pf_destroy = spdif_component_destroy;

   /* Allocate and initialise all the ports for this component */
   component->input = mmal_ports_alloc(component, 1, MMAL_PORT_TYPE_INPUT, sizeof(MMAL_PORT_MODULE_T));
   if(!component->input)
      goto error;
   component->input_num = 1;
   component->input[0]->priv->pf_enable = spdif_port_enable;
   component->input[0]->priv->pf_disable = spdif_port_disable;
   component->input[0]->priv->pf_flush = spdif_port_flush;
   component->input[0]->priv->pf_send = spdif_port_send;
   component->input[0]->priv->pf_set_format = spdif_input_port_format_commit;
   component->input[0]->priv->module->queue = mmal_queue_create();
   if(!component->input[0]->priv->module->queue)
      goto error;

   component->output = mmal_ports_alloc(component, 1, MMAL_PORT_TYPE_OUTPUT, sizeof(MMAL_PORT_MODULE_T));
   if(!component->output)
      goto error;
   component->output_num = 1;
   component->output[0]->priv->pf_enable = spdif_port_enable;
   component->output[0]->priv->pf_disable = spdif_port_disable;
   component->output[0]->priv->pf_flush = spdif_port_flush;
   component->output[0]->priv->pf_send = spdif_port_send;
   component->output[0]->priv->pf_set_format = spdif_output_port_format_commit;
   component->output[0]->priv->module->queue = mmal_queue_create();
   if(!component->output[0]->priv->module->queue)
      goto error;

   status = mmal_component_action_register(component, spdif_do_processing_loop);
   if (status != MMAL_SUCCESS)
      goto error;

   component->input[0]->format->type = MMAL_ES_TYPE_AUDIO;
   component->input[0]->format->encoding = MMAL_ENCODING_AC3;
   component->input[0]->buffer_size_min =
      component->input[0]->buffer_size_recommended = INPUT_MIN_BUFFER_SIZE;
   component->input[0]->buffer_num_min =
      component->input[0]->buffer_num_recommended = INPUT_MIN_BUFFER_NUM;

   component->output[0]->format->type = MMAL_ES_TYPE_AUDIO;
   component->output[0]->format->encoding = MMAL_ENCODING_AC3;
   component->output[0]->format->es->audio.channels = 2;
   component->output[0]->format->es->audio.bits_per_sample = 16;
   component->output[0]->buffer_size_min =
      component->output[0]->buffer_size_recommended = OUTPUT_MIN_BUFFER_SIZE;
   component->output[0]->buffer_num_min =
      component->output[0]->buffer_num_recommended = OUTPUT_MIN_BUFFER_NUM;

   return MMAL_SUCCESS;

 error:
   spdif_component_destroy(component);
   return status;
}
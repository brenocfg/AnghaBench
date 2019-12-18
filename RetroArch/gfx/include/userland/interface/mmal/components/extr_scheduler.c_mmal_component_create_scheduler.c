#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {unsigned int input_num; unsigned int output_num; int /*<<< orphan*/  clock_num; int /*<<< orphan*/  clock; TYPE_7__** output; TYPE_4__** input; TYPE_1__* priv; } ;
struct TYPE_20__ {int buffer_num_min; TYPE_6__* priv; int /*<<< orphan*/  capabilities; scalar_t__ buffer_num_recommended; } ;
struct TYPE_19__ {TYPE_5__* module; void* pf_parameter_set; int /*<<< orphan*/  pf_set_format; void* pf_send; void* pf_flush; void* pf_disable; void* pf_enable; } ;
struct TYPE_18__ {void* queue; } ;
struct TYPE_17__ {int buffer_num_min; TYPE_3__* priv; int /*<<< orphan*/  capabilities; scalar_t__ buffer_num_recommended; } ;
struct TYPE_16__ {TYPE_2__* module; void* pf_parameter_set; int /*<<< orphan*/  pf_set_format; void* pf_send; void* pf_flush; void* pf_disable; void* pf_enable; } ;
struct TYPE_15__ {int /*<<< orphan*/  last_ts; void* queue; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* pf_destroy ) (TYPE_8__*) ;int /*<<< orphan*/ * module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_MODULE_T ;
typedef  TYPE_8__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*) ; 
 scalar_t__ MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_PORT_CAPABILITY_PASSTHROUGH ; 
 int /*<<< orphan*/  MMAL_PORT_CAPABILITY_SUPPORTS_EVENT_FORMAT_CHANGE ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_INPUT ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TIME_UNKNOWN ; 
 int /*<<< orphan*/  SCHEDULER_CLOCK_PORTS_NUM ; 
 void* SCHEDULER_INPUT_PORTS_NUM ; 
 void* SCHEDULER_OUTPUT_PORTS_NUM ; 
 scalar_t__ mmal_component_action_register (TYPE_8__*,int /*<<< orphan*/ ) ; 
 void* mmal_ports_alloc (TYPE_8__*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmal_ports_clock_alloc (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* mmal_queue_create () ; 
 int /*<<< orphan*/  scheduler_component_action ; 
 int /*<<< orphan*/  scheduler_component_destroy (TYPE_8__*) ; 
 int /*<<< orphan*/  scheduler_input_port_format_commit ; 
 int /*<<< orphan*/  scheduler_output_port_format_commit ; 
 void* scheduler_port_disable ; 
 void* scheduler_port_enable ; 
 void* scheduler_port_flush ; 
 void* scheduler_port_parameter_set ; 
 void* scheduler_port_send ; 
 scalar_t__ strstr (char const*,char*) ; 
 int /*<<< orphan*/ * vcos_calloc (int,int,char*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_component_create_scheduler(const char *name, MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module;
   MMAL_STATUS_T status = MMAL_ENOMEM;
   int disable_passthrough = 0;
   unsigned int i;

   /* Allocate the context for our module */
   component->priv->module = module = vcos_calloc(1, sizeof(*module), "mmal module");
   if (!module)
      return MMAL_ENOMEM;

   component->priv->pf_destroy = scheduler_component_destroy;

   /* Allocate and initialise all the ports for this component */
   component->input = mmal_ports_alloc(component, SCHEDULER_INPUT_PORTS_NUM,
                                       MMAL_PORT_TYPE_INPUT, sizeof(MMAL_PORT_MODULE_T));
   if (!component->input)
      goto error;
   component->input_num = SCHEDULER_INPUT_PORTS_NUM;
   for (i = 0; i < component->input_num; i++)
   {
      component->input[i]->priv->pf_enable = scheduler_port_enable;
      component->input[i]->priv->pf_disable = scheduler_port_disable;
      component->input[i]->priv->pf_flush = scheduler_port_flush;
      component->input[i]->priv->pf_send = scheduler_port_send;
      component->input[i]->priv->pf_set_format = scheduler_input_port_format_commit;
      component->input[i]->priv->pf_parameter_set = scheduler_port_parameter_set;
      component->input[i]->buffer_num_min = 1;
      component->input[i]->buffer_num_recommended = 0;
      component->input[i]->capabilities = MMAL_PORT_CAPABILITY_SUPPORTS_EVENT_FORMAT_CHANGE;
      component->input[i]->priv->module->queue = mmal_queue_create();
      if (!component->input[i]->priv->module->queue)
         goto error;
      component->input[i]->priv->module->last_ts = MMAL_TIME_UNKNOWN;
   }

   /* Override passthrough behaviour */
   if (strstr(name, ".copy"))
   {
      LOG_TRACE("disable passthrough on output ports");
      disable_passthrough = 1;
   }

   component->output = mmal_ports_alloc(component, SCHEDULER_OUTPUT_PORTS_NUM,
                                        MMAL_PORT_TYPE_OUTPUT, sizeof(MMAL_PORT_MODULE_T));
   if (!component->output)
      goto error;
   component->output_num = SCHEDULER_OUTPUT_PORTS_NUM;
   for (i = 0; i < component->output_num; i++)
   {
      component->output[i]->priv->pf_enable = scheduler_port_enable;
      component->output[i]->priv->pf_disable = scheduler_port_disable;
      component->output[i]->priv->pf_flush = scheduler_port_flush;
      component->output[i]->priv->pf_send = scheduler_port_send;
      component->output[i]->priv->pf_set_format = scheduler_output_port_format_commit;
      component->output[i]->priv->pf_parameter_set = scheduler_port_parameter_set;
      component->output[i]->buffer_num_min = 1;
      component->output[i]->buffer_num_recommended = 0;
      component->output[i]->capabilities = disable_passthrough ? 0 : MMAL_PORT_CAPABILITY_PASSTHROUGH;
      component->output[i]->priv->module->queue = mmal_queue_create();
      if (!component->output[i]->priv->module->queue)
         goto error;
   }

   /* Create the clock port (clock ports are managed by the framework) */
   component->clock = mmal_ports_clock_alloc(component, SCHEDULER_CLOCK_PORTS_NUM, 0, NULL);
   if (!component->clock)
      goto error;
   component->clock_num = SCHEDULER_CLOCK_PORTS_NUM;

   status = mmal_component_action_register(component, scheduler_component_action);
   if (status != MMAL_SUCCESS)
      goto error;

   return MMAL_SUCCESS;

error:
   scheduler_component_destroy(component);
   return status;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int input_num; int output_num; TYPE_7__** output; TYPE_4__** input; TYPE_1__* priv; } ;
struct TYPE_18__ {int buffer_num_min; TYPE_6__* priv; int /*<<< orphan*/  capabilities; scalar_t__ buffer_num_recommended; } ;
struct TYPE_17__ {TYPE_5__* module; void* pf_parameter_set; void* pf_set_format; void* pf_send; void* pf_flush; void* pf_disable; void* pf_enable; } ;
struct TYPE_16__ {void* queue; } ;
struct TYPE_15__ {int buffer_num_min; TYPE_3__* priv; scalar_t__ buffer_num_recommended; } ;
struct TYPE_14__ {TYPE_2__* module; void* pf_parameter_set; void* pf_set_format; void* pf_send; void* pf_flush; void* pf_disable; void* pf_enable; } ;
struct TYPE_13__ {void* queue; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* pf_destroy ) (TYPE_8__*) ;int /*<<< orphan*/ * module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_MODULE_T ;
typedef  TYPE_8__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (char const*) ; 
 int /*<<< orphan*/  MMAL_PORT_CAPABILITY_PASSTHROUGH ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_INPUT ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_OUTPUT ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int SPLITTER_OUTPUT_PORTS_NUM ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* mmal_ports_alloc (TYPE_8__*,int,int /*<<< orphan*/ ,int) ; 
 void* mmal_queue_create () ; 
 int /*<<< orphan*/  splitter_component_destroy (TYPE_8__*) ; 
 void* splitter_port_disable ; 
 void* splitter_port_enable ; 
 void* splitter_port_flush ; 
 void* splitter_port_format_commit ; 
 void* splitter_port_parameter_set ; 
 void* splitter_port_send ; 
 int /*<<< orphan*/ * vcos_malloc (int,char*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_component_create_splitter(const char *name, MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module;
   MMAL_STATUS_T status = MMAL_ENOMEM;
   unsigned int i;
   MMAL_PARAM_UNUSED(name);

   /* Allocate the context for our module */
   component->priv->module = module = vcos_malloc(sizeof(*module), "mmal module");
   if (!module)
      return MMAL_ENOMEM;
   memset(module, 0, sizeof(*module));

   component->priv->pf_destroy = splitter_component_destroy;

   /* Allocate and initialise all the ports for this component */
   component->input = mmal_ports_alloc(component, 1, MMAL_PORT_TYPE_INPUT, sizeof(MMAL_PORT_MODULE_T));
   if(!component->input)
      goto error;
   component->input_num = 1;
   component->input[0]->priv->pf_enable = splitter_port_enable;
   component->input[0]->priv->pf_disable = splitter_port_disable;
   component->input[0]->priv->pf_flush = splitter_port_flush;
   component->input[0]->priv->pf_send = splitter_port_send;
   component->input[0]->priv->pf_set_format = splitter_port_format_commit;
   component->input[0]->priv->pf_parameter_set = splitter_port_parameter_set;
   component->input[0]->buffer_num_min = 1;
   component->input[0]->buffer_num_recommended = 0;
   component->input[0]->priv->module->queue = mmal_queue_create();
   if(!component->input[0]->priv->module->queue)
      goto error;

   component->output = mmal_ports_alloc(component, SPLITTER_OUTPUT_PORTS_NUM,
                                        MMAL_PORT_TYPE_OUTPUT, sizeof(MMAL_PORT_MODULE_T));
   if(!component->output)
      goto error;
   component->output_num = SPLITTER_OUTPUT_PORTS_NUM;
   for(i = 0; i < component->output_num; i++)
   {
      component->output[i]->priv->pf_enable = splitter_port_enable;
      component->output[i]->priv->pf_disable = splitter_port_disable;
      component->output[i]->priv->pf_flush = splitter_port_flush;
      component->output[i]->priv->pf_send = splitter_port_send;
      component->output[i]->priv->pf_set_format = splitter_port_format_commit;
      component->output[i]->priv->pf_parameter_set = splitter_port_parameter_set;
      component->output[i]->buffer_num_min = 1;
      component->output[i]->buffer_num_recommended = 0;
      component->output[i]->capabilities = MMAL_PORT_CAPABILITY_PASSTHROUGH;
      component->output[i]->priv->module->queue = mmal_queue_create();
      if(!component->output[i]->priv->module->queue)
         goto error;
   }

   return MMAL_SUCCESS;

 error:
   splitter_component_destroy(component);
   return status;
}
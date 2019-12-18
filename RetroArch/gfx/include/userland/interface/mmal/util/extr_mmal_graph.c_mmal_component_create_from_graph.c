#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_35__ {int /*<<< orphan*/  name; TYPE_8__* priv; } ;
struct TYPE_34__ {int /*<<< orphan*/  pf_parameter_set; int /*<<< orphan*/  pf_parameter_get; } ;
struct TYPE_33__ {int /*<<< orphan*/  pf_disable; int /*<<< orphan*/  pf_enable; int /*<<< orphan*/  (* pf_destroy ) (TYPE_12__*) ;TYPE_11__* module; } ;
struct TYPE_32__ {TYPE_16__* control; } ;
struct TYPE_31__ {void* user_data; int /*<<< orphan*/  callback; } ;
struct TYPE_30__ {TYPE_3__* priv; } ;
struct TYPE_29__ {scalar_t__ pf_connect; } ;
struct TYPE_28__ {TYPE_1__* priv; } ;
struct TYPE_27__ {scalar_t__ pf_connect; } ;
struct TYPE_26__ {void* userdata; } ;
struct TYPE_25__ {TYPE_10__* priv; } ;
struct TYPE_24__ {unsigned int input_num; unsigned int output_num; unsigned int clock_num; TYPE_9__* control; TYPE_7__* priv; TYPE_13__** clock; TYPE_13__** output; TYPE_13__** input; } ;
struct TYPE_23__ {unsigned int input_num; unsigned int output_num; unsigned int clock_num; unsigned int connection_num; unsigned int component_num; TYPE_6__** component; TYPE_12__* graph_component; TYPE_5__** connection; TYPE_4__** output; TYPE_2__** input; } ;
struct TYPE_22__ {void* pf_payload_free; void* pf_payload_alloc; int /*<<< orphan*/ * pf_connect; void* pf_parameter_set; void* pf_parameter_get; void* pf_set_format; void* pf_send; void* pf_flush; void* pf_disable; void* pf_enable; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_11__ MMAL_GRAPH_PRIVATE_T ;
typedef  TYPE_12__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (char const*) ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_INPUT ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  graph_component_connection_cb ; 
 int /*<<< orphan*/  graph_component_control_cb ; 
 int /*<<< orphan*/  graph_component_destroy (TYPE_12__*) ; 
 int /*<<< orphan*/  graph_component_disable ; 
 int /*<<< orphan*/  graph_component_enable ; 
 int /*<<< orphan*/  graph_do_processing_loop ; 
 void* graph_port_connect ; 
 int /*<<< orphan*/  graph_port_control_parameter_get ; 
 int /*<<< orphan*/  graph_port_control_parameter_set ; 
 void* graph_port_disable ; 
 void* graph_port_enable ; 
 void* graph_port_flush ; 
 void* graph_port_format_commit ; 
 void* graph_port_parameter_get ; 
 void* graph_port_parameter_set ; 
 void* graph_port_payload_alloc ; 
 void* graph_port_payload_free ; 
 void* graph_port_send ; 
 scalar_t__ graph_port_update (TYPE_11__*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_component_action_register (TYPE_12__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmal_port_enable (TYPE_16__*,int /*<<< orphan*/ ) ; 
 void* mmal_ports_alloc (TYPE_12__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__** mmal_ports_clock_alloc (TYPE_12__*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_component_create_from_graph(const char *name, MMAL_COMPONENT_T *component)
{
   MMAL_STATUS_T status = MMAL_ENOMEM;
   /* Our context is already allocated and available */
   MMAL_GRAPH_PRIVATE_T *graph = component->priv->module;
   unsigned int i;
   MMAL_PARAM_UNUSED(name);

   component->control->priv->pf_parameter_get = graph_port_control_parameter_get;
   component->control->priv->pf_parameter_set = graph_port_control_parameter_set;

   /* Allocate the ports for this component */
   if(graph->input_num)
   {
      component->input = mmal_ports_alloc(component, graph->input_num, MMAL_PORT_TYPE_INPUT, 0);
      if(!component->input)
         goto error;
   }
   component->input_num = graph->input_num;
   for(i = 0; i < component->input_num; i++)
   {
      component->input[i]->priv->pf_enable = graph_port_enable;
      component->input[i]->priv->pf_disable = graph_port_disable;
      component->input[i]->priv->pf_flush = graph_port_flush;
      component->input[i]->priv->pf_send = graph_port_send;
      component->input[i]->priv->pf_set_format = graph_port_format_commit;
      component->input[i]->priv->pf_parameter_get = graph_port_parameter_get;
      component->input[i]->priv->pf_parameter_set = graph_port_parameter_set;
      if (graph->input[i]->priv->pf_connect && 0 /* FIXME: disabled for now */)
         component->input[i]->priv->pf_connect = graph_port_connect;
      component->input[i]->priv->pf_payload_alloc = graph_port_payload_alloc;
      component->input[i]->priv->pf_payload_free = graph_port_payload_free;

      /* Mirror the port values */
      status = graph_port_update(graph, component->input[i], MMAL_TRUE);
      if (status != MMAL_SUCCESS)
         goto error;
   }
   if(graph->output_num)
   {
      component->output = mmal_ports_alloc(component, graph->output_num, MMAL_PORT_TYPE_OUTPUT, 0);
      if(!component->output)
         goto error;
   }
   component->output_num = graph->output_num;
   for(i = 0; i < component->output_num; i++)
   {
      component->output[i]->priv->pf_enable = graph_port_enable;
      component->output[i]->priv->pf_disable = graph_port_disable;
      component->output[i]->priv->pf_flush = graph_port_flush;
      component->output[i]->priv->pf_send = graph_port_send;
      component->output[i]->priv->pf_set_format = graph_port_format_commit;
      component->output[i]->priv->pf_parameter_get = graph_port_parameter_get;
      component->output[i]->priv->pf_parameter_set = graph_port_parameter_set;
      if (graph->output[i]->priv->pf_connect && 0 /* FIXME: disabled for now */)
         component->output[i]->priv->pf_connect = graph_port_connect;
      component->output[i]->priv->pf_payload_alloc = graph_port_payload_alloc;
      component->output[i]->priv->pf_payload_free = graph_port_payload_free;

      /* Mirror the port values */
      status = graph_port_update(graph, component->output[i], MMAL_TRUE);
      if (status != MMAL_SUCCESS)
         goto error;
   }
   if(graph->clock_num)
   {
      component->clock = mmal_ports_clock_alloc(component, graph->clock_num, 0, NULL);
      if(!component->clock)
      {
         status = MMAL_ENOMEM;
         goto error;
      }
   }
   component->clock_num = graph->clock_num;
   for(i = 0; i < component->clock_num; i++)
   {
      component->clock[i]->priv->pf_enable = graph_port_enable;
      component->clock[i]->priv->pf_disable = graph_port_disable;
      component->clock[i]->priv->pf_flush = graph_port_flush;
      component->clock[i]->priv->pf_send = graph_port_send;
      component->clock[i]->priv->pf_set_format = graph_port_format_commit;
      component->clock[i]->priv->pf_parameter_get = graph_port_parameter_get;
      component->clock[i]->priv->pf_parameter_set = graph_port_parameter_set;
      component->clock[i]->priv->pf_connect = NULL; /* FIXME: disabled for now */
      component->clock[i]->priv->pf_payload_alloc = graph_port_payload_alloc;
      component->clock[i]->priv->pf_payload_free = graph_port_payload_free;

      /* Mirror the port values */
      status = graph_port_update(graph, component->clock[i], MMAL_TRUE);
      if (status != MMAL_SUCCESS)
         goto error;
   }

   status = mmal_component_action_register(component, graph_do_processing_loop);
   if (status != MMAL_SUCCESS)
      goto error;

#if 1 // FIXME
   /* Set our connection callback */
   for (i = 0; i < graph->connection_num; i++)
   {
      graph->connection[i]->callback = graph_component_connection_cb;
      graph->connection[i]->user_data = (void *)component;
   }
#endif

   component->priv->pf_destroy = graph_component_destroy;
   component->priv->pf_enable = graph_component_enable;
   component->priv->pf_disable = graph_component_disable;
   graph->graph_component = component;

   /* Enable all the control ports */
   for (i = 0; i < graph->component_num; i++)
   {
      graph->component[i]->control->userdata = (void *)component;
      status = mmal_port_enable(graph->component[i]->control, graph_component_control_cb);
      if (status != MMAL_SUCCESS)
         LOG_ERROR("could not enable port %s", component->control->name);
   }

   return MMAL_SUCCESS;

 error:
   graph_component_destroy(component);
   return status;
}
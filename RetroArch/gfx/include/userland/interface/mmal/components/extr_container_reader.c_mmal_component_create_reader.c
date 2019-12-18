#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__* priv; } ;
struct TYPE_17__ {unsigned int output_num; TYPE_5__* control; TYPE_7__** output; TYPE_1__* priv; } ;
struct TYPE_16__ {TYPE_4__* priv; } ;
struct TYPE_15__ {int /*<<< orphan*/  pf_parameter_set; } ;
struct TYPE_14__ {TYPE_2__* module; int /*<<< orphan*/  pf_send; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_disable; int /*<<< orphan*/  pf_enable; } ;
struct TYPE_13__ {int /*<<< orphan*/  queue; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* pf_destroy ) (TYPE_6__*) ;int /*<<< orphan*/ * module; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_MODULE_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 scalar_t__ MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (char const*) ; 
 int /*<<< orphan*/  MMAL_PORT_TYPE_OUTPUT ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  container_component_destroy (TYPE_6__*) ; 
 int /*<<< orphan*/  container_port_disable ; 
 int /*<<< orphan*/  container_port_enable ; 
 int /*<<< orphan*/  container_port_flush ; 
 int /*<<< orphan*/  container_port_send ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmal_component_action_register (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_7__** mmal_ports_alloc (TYPE_6__*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmal_queue_create () ; 
 int /*<<< orphan*/  reader_do_processing ; 
 int /*<<< orphan*/  reader_parameter_set ; 
 int /*<<< orphan*/ * vcos_malloc (int,char*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_component_create_reader(const char *name, MMAL_COMPONENT_T *component)
{
   MMAL_COMPONENT_MODULE_T *module;
   unsigned int outputs_num, i;
   MMAL_STATUS_T status = MMAL_ENOMEM;
   MMAL_PARAM_UNUSED(name);

   /* Allocate the context for our module */
   component->priv->module = module = vcos_malloc(sizeof(*module), "mmal module");
   if (!module)
      return MMAL_ENOMEM;
   memset(module, 0, sizeof(*module));

   component->priv->pf_destroy = container_component_destroy;

   /* Create 3 tracks for now (audio/video/subpicture).
    * FIXME: ideally we should create 1 track per elementary stream. */
   outputs_num = 3;

   /* Now the component on reader has been created, we can allocate
    * the ports for this component */
   component->output = mmal_ports_alloc(component, outputs_num, MMAL_PORT_TYPE_OUTPUT,
                                        sizeof(MMAL_PORT_MODULE_T));
   if(!component->output)
      goto error;
   component->output_num = outputs_num;

   for(i = 0; i < outputs_num; i++)
   {
      component->output[i]->priv->pf_enable = container_port_enable;
      component->output[i]->priv->pf_disable = container_port_disable;
      component->output[i]->priv->pf_flush = container_port_flush;
      component->output[i]->priv->pf_send = container_port_send;
      component->output[i]->priv->module->queue = mmal_queue_create();
      if(!component->output[i]->priv->module->queue)
         goto error;
   }
   component->control->priv->pf_parameter_set = reader_parameter_set;

   status = mmal_component_action_register(component, reader_do_processing);
   if (status != MMAL_SUCCESS)
      goto error;

   return MMAL_SUCCESS;

 error:
   container_component_destroy(component);
   return status;
}
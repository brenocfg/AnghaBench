#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__** input; } ;
struct TYPE_9__ {TYPE_4__* component; TYPE_2__* priv; int /*<<< orphan*/  format; } ;
struct TYPE_8__ {TYPE_1__* module; } ;
struct TYPE_7__ {scalar_t__ needs_configuring; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PORT_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_component_action_trigger (TYPE_4__*) ; 
 scalar_t__ mmal_format_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T copy_output_port_format_commit(MMAL_PORT_T *out)
{
   MMAL_COMPONENT_T *component = out->component;
   MMAL_PORT_T *in = component->input[0];

   /* The format of the output port needs to match the input port */
   if (mmal_format_compare(out->format, in->format))
      return MMAL_EINVAL;

   out->priv->module->needs_configuring = 0;
   mmal_component_action_trigger(out->component);
   return MMAL_SUCCESS;
}
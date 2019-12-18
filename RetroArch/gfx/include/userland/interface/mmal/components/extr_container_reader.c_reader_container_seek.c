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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_SEEK_FLAGS_T ;
struct TYPE_18__ {int /*<<< orphan*/  container; } ;
struct TYPE_17__ {unsigned int output_num; TYPE_4__** output; TYPE_1__* priv; } ;
struct TYPE_16__ {int flags; int /*<<< orphan*/  offset; } ;
struct TYPE_15__ {TYPE_3__* priv; } ;
struct TYPE_14__ {TYPE_2__* module; } ;
struct TYPE_13__ {int /*<<< orphan*/  flush; int /*<<< orphan*/  eos; } ;
struct TYPE_12__ {TYPE_7__* module; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_5__ MMAL_PARAMETER_SEEK_T ;
typedef  TYPE_6__ MMAL_COMPONENT_T ;
typedef  TYPE_7__ MMAL_COMPONENT_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_FALSE ; 
 int MMAL_PARAM_SEEK_FLAG_FORWARD ; 
 int MMAL_PARAM_SEEK_FLAG_PRECISE ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  VC_CONTAINER_SEEK_FLAG_FORWARD ; 
 int /*<<< orphan*/  VC_CONTAINER_SEEK_FLAG_PRECISE ; 
 int /*<<< orphan*/  VC_CONTAINER_SEEK_MODE_TIME ; 
 int /*<<< orphan*/  container_map_to_mmal_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_component_action_lock (TYPE_6__*) ; 
 int /*<<< orphan*/  mmal_component_action_unlock (TYPE_6__*) ; 
 int /*<<< orphan*/  vc_container_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T reader_container_seek(MMAL_COMPONENT_T *component, const MMAL_PARAMETER_SEEK_T *seek)
{
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   VC_CONTAINER_SEEK_FLAGS_T flags = 0;
   int64_t offset = seek->offset;
   VC_CONTAINER_STATUS_T cstatus;
   unsigned int i;

   if(seek->flags & MMAL_PARAM_SEEK_FLAG_PRECISE)
      flags |= VC_CONTAINER_SEEK_FLAG_PRECISE;
   if(seek->flags & MMAL_PARAM_SEEK_FLAG_FORWARD)
      flags |= VC_CONTAINER_SEEK_FLAG_FORWARD;

   mmal_component_action_lock(component);
   for(i = 0; i < component->output_num; i++)
   {
      component->output[i]->priv->module->eos = MMAL_FALSE;
      component->output[i]->priv->module->flush = MMAL_TRUE;
   }
   cstatus = vc_container_seek( module->container, &offset, VC_CONTAINER_SEEK_MODE_TIME, flags);
   mmal_component_action_unlock(component);
   return container_map_to_mmal_status(cstatus);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int actions; int /*<<< orphan*/  enabled; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_5__* ports; } ;
typedef  size_t OMX_U32 ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int MMALOMX_ACTION_CHECK_ALLOCATED ; 
 int MMALOMX_ACTION_ENABLE ; 
 int MMALOMX_ACTION_NOTIFY_ENABLE ; 
 int /*<<< orphan*/  MMALOMX_LOCK_PORT (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  MMALOMX_UNLOCK_PORT (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  OMX_CommandPortEnable ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_EventCmdComplete ; 
 scalar_t__ OMX_StateLoaded ; 
 scalar_t__ OMX_StateWaitForResources ; 
 int /*<<< orphan*/  mmalomx_callback_event_handler (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmalomx_commands_actions_check (TYPE_1__*) ; 

OMX_ERRORTYPE mmalomx_command_port_enable(
   OMX_HANDLETYPE hComponent,
   OMX_U32 nPortIndex)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   component->ports[nPortIndex].enabled = MMAL_TRUE;

   if (component->state == OMX_StateLoaded ||
       component->state == OMX_StateWaitForResources)
   {
      mmalomx_callback_event_handler(component, OMX_EventCmdComplete, OMX_CommandPortEnable, nPortIndex, NULL);
      return OMX_ErrorNone;
   }

   MMALOMX_LOCK_PORT(component, &component->ports[nPortIndex]);
   component->ports[nPortIndex].actions =
      MMALOMX_ACTION_CHECK_ALLOCATED|MMALOMX_ACTION_ENABLE|MMALOMX_ACTION_NOTIFY_ENABLE;
   MMALOMX_UNLOCK_PORT(component, &component->ports[nPortIndex]);

   mmalomx_commands_actions_check(component);

   return OMX_ErrorNone;
}
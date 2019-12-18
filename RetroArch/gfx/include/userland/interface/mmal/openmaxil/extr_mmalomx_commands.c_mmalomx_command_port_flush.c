#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int actions; } ;
struct TYPE_7__ {TYPE_4__* ports; } ;
typedef  size_t OMX_U32 ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int MMALOMX_ACTION_CHECK_FLUSHED ; 
 int MMALOMX_ACTION_FLUSH ; 
 int MMALOMX_ACTION_NOTIFY_FLUSH ; 
 int /*<<< orphan*/  MMALOMX_LOCK_PORT (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  MMALOMX_UNLOCK_PORT (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  mmalomx_commands_actions_check (TYPE_1__*) ; 

OMX_ERRORTYPE mmalomx_command_port_flush(
   OMX_HANDLETYPE hComponent,
   OMX_U32 nPortIndex)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;

   MMALOMX_LOCK_PORT(component, &component->ports[nPortIndex]);
   component->ports[nPortIndex].actions =
      MMALOMX_ACTION_FLUSH|MMALOMX_ACTION_CHECK_FLUSHED|MMALOMX_ACTION_NOTIFY_FLUSH;
   MMALOMX_UNLOCK_PORT(component, &component->ports[nPortIndex]);

   mmalomx_commands_actions_check(component);

   return OMX_ErrorNone;
}
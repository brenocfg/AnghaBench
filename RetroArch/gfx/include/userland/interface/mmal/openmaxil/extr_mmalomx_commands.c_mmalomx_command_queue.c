#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  cmd_queue; TYPE_1__* cmd_pool; } ;
struct TYPE_10__ {void* offset; void* cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  queue; } ;
typedef  void* OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;
typedef  TYPE_3__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  OMX_ErrorInsufficientResources ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 TYPE_2__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  mmalomx_commands_actions_signal (TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_verify (TYPE_2__*) ; 

OMX_ERRORTYPE mmalomx_command_queue(
   MMALOMX_COMPONENT_T *component,
   OMX_U32 arg1, OMX_U32 arg2)
{
   MMAL_BUFFER_HEADER_T *cmd = mmal_queue_get(component->cmd_pool->queue);

   if (!vcos_verify(cmd))
   {
      LOG_ERROR("command queue too small");
      return OMX_ErrorInsufficientResources;
   }

   cmd->cmd = arg1;
   cmd->offset = arg2;
   mmal_queue_put(component->cmd_queue, cmd);

   mmalomx_commands_actions_signal(component);

   return OMX_ErrorNone;
}
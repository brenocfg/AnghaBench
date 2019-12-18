#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  cmd_queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ MMAL_BUFFER_HEADER_T ;
typedef  TYPE_2__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_ErrorNoMore ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_1__*) ; 
 TYPE_1__* mmal_queue_get (int /*<<< orphan*/ ) ; 

OMX_ERRORTYPE mmalomx_command_dequeue(
   MMALOMX_COMPONENT_T *component,
   OMX_U32 *arg1, OMX_U32 *arg2)
{
   MMAL_BUFFER_HEADER_T *cmd = mmal_queue_get(component->cmd_queue);
   if (!cmd)
      return OMX_ErrorNoMore;

   *arg1 = cmd->cmd;
   *arg2 = cmd->offset;
   mmal_buffer_header_release(cmd);
   return OMX_ErrorNone;
}
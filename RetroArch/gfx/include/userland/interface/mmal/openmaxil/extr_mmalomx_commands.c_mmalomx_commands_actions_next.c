#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int ports_num; int /*<<< orphan*/  omx; } ;
typedef  unsigned int OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_HANDLETYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  scalar_t__ OMX_COMMANDTYPE ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 unsigned int OMX_ALL ; 
 scalar_t__ OMX_CommandFlush ; 
 scalar_t__ OMX_CommandPortDisable ; 
 scalar_t__ OMX_CommandPortEnable ; 
 scalar_t__ OMX_CommandStateSet ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ mmalomx_command_dequeue (TYPE_1__*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  mmalomx_command_port_disable (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mmalomx_command_port_enable (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mmalomx_command_port_flush (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mmalomx_command_state_set (int /*<<< orphan*/ ,unsigned int) ; 

void mmalomx_commands_actions_next(MMALOMX_COMPONENT_T *component)
{
   OMX_ERRORTYPE status = OMX_ErrorNone;
   OMX_COMMANDTYPE cmd;
   OMX_U32 arg1, arg2, nParam1;
   unsigned int i;

   status = mmalomx_command_dequeue(component, &arg1, &arg2);
   if (status != OMX_ErrorNone)
      return;

   cmd = (OMX_COMMANDTYPE)arg1;
   nParam1 = arg2;

   if (cmd == OMX_CommandStateSet)
   {
      mmalomx_command_state_set((OMX_HANDLETYPE)&component->omx, nParam1);
   }
   else if (cmd == OMX_CommandFlush)
   {
      for (i = 0; i < component->ports_num; i++)
         if (i == nParam1 || nParam1 == OMX_ALL)
            mmalomx_command_port_flush((OMX_HANDLETYPE)&component->omx, i);
   }
   else if (cmd == OMX_CommandPortEnable)
   {
      for (i = 0; i < component->ports_num; i++)
         if (i == nParam1 || nParam1 == OMX_ALL)
            mmalomx_command_port_enable((OMX_HANDLETYPE)&component->omx, i);
   }
   else if (cmd == OMX_CommandPortDisable)
   {
      for (i = 0; i < component->ports_num; i++)
         if (i == nParam1 || nParam1 == OMX_ALL)
            mmalomx_command_port_disable((OMX_HANDLETYPE)&component->omx, i);
   }
}
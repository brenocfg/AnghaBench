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
struct TYPE_4__ {int /*<<< orphan*/  comp; } ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_1__ COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_CommandPortEnable ; 
 scalar_t__ OMX_ErrorNone ; 
 scalar_t__ OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ilclient_wait_for_command_complete (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vc_assert (int) ; 

void ilclient_enable_port(COMPONENT_T *comp, int portIndex)
{
   OMX_ERRORTYPE error;
   error = OMX_SendCommand(comp->comp, OMX_CommandPortEnable, portIndex, NULL);
   vc_assert(error == OMX_ErrorNone);
   if(ilclient_wait_for_command_complete(comp, OMX_CommandPortEnable, portIndex) < 0)
      vc_assert(0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  comp; } ;
typedef  int /*<<< orphan*/  OMX_STATETYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_1__ COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  OMX_CommandStateSet ; 
 scalar_t__ OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_EventError ; 
 scalar_t__ OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilclient_debug_output (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilclient_remove_event (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ilclient_wait_for_command_complete (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_assert (int) ; 

int ilclient_change_component_state(COMPONENT_T *comp, OMX_STATETYPE state)
{
   OMX_ERRORTYPE error;
   error = OMX_SendCommand(comp->comp, OMX_CommandStateSet, state, NULL);
   vc_assert(error == OMX_ErrorNone);
   if(ilclient_wait_for_command_complete(comp, OMX_CommandStateSet, state) < 0)
   {
      ilclient_debug_output("ilclient: could not change component state to %d", state);
      ilclient_remove_event(comp, OMX_EventError, 0, 1, 0, 1);
      return -1;
   }
   return 0;
}
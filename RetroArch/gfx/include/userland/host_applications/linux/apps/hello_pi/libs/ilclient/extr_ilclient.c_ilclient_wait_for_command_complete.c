#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_COMMANDTYPE ;
typedef  int /*<<< orphan*/  COMPONENT_T ;

/* Variables and functions */
 int ilclient_wait_for_command_complete_dual (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ilclient_wait_for_command_complete(COMPONENT_T *comp, OMX_COMMANDTYPE command, OMX_U32 nData2)
{
   return ilclient_wait_for_command_complete_dual(comp, command, nData2, NULL);
}
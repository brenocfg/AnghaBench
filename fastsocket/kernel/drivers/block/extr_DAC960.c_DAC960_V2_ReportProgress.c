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
struct TYPE_4__ {int EphemeralProgressMessage; int /*<<< orphan*/  ControllerNumber; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_Progress (char*,TYPE_1__*,unsigned char*,unsigned int,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static void DAC960_V2_ReportProgress(DAC960_Controller_T *Controller,
				     unsigned char *MessageString,
				     unsigned int LogicalDeviceNumber,
				     unsigned long BlocksCompleted,
				     unsigned long LogicalDeviceSize)
{
  Controller->EphemeralProgressMessage = true;
  DAC960_Progress("%s in Progress: Logical Drive %d (/dev/rd/c%dd%d) "
		  "%d%% completed\n", Controller,
		  MessageString,
		  LogicalDeviceNumber,
		  Controller->ControllerNumber,
		  LogicalDeviceNumber,
		  (100 * (BlocksCompleted >> 7)) / (LogicalDeviceSize >> 7));
  Controller->EphemeralProgressMessage = false;
}
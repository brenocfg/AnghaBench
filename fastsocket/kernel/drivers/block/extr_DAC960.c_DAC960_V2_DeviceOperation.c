#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int DataTransferControllerToHost; int NoAutoRequestSense; } ;
struct TYPE_11__ {int /*<<< orphan*/  OperationDevice; int /*<<< orphan*/  IOCTL_Opcode; TYPE_1__ CommandControlBits; int /*<<< orphan*/  CommandOpcode; } ;
struct TYPE_13__ {TYPE_2__ DeviceOperation; } ;
struct TYPE_12__ {scalar_t__ CommandStatus; TYPE_4__ CommandMailbox; } ;
struct TYPE_14__ {TYPE_3__ V2; int /*<<< orphan*/  CommandType; } ;
typedef  int /*<<< orphan*/  DAC960_V2_OperationDevice_T ;
typedef  int /*<<< orphan*/  DAC960_V2_IOCTL_Opcode_T ;
typedef  scalar_t__ DAC960_V2_CommandStatus_T ;
typedef  TYPE_4__ DAC960_V2_CommandMailbox_T ;
typedef  int /*<<< orphan*/  DAC960_Controller_T ;
typedef  TYPE_5__ DAC960_Command_T ;

/* Variables and functions */
 TYPE_5__* DAC960_AllocateCommand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DAC960_DeallocateCommand (TYPE_5__*) ; 
 int /*<<< orphan*/  DAC960_ExecuteCommand (TYPE_5__*) ; 
 int /*<<< orphan*/  DAC960_ImmediateCommand ; 
 int /*<<< orphan*/  DAC960_V2_ClearCommand (TYPE_5__*) ; 
 int /*<<< orphan*/  DAC960_V2_IOCTL ; 
 scalar_t__ DAC960_V2_NormalCompletion ; 

__attribute__((used)) static bool DAC960_V2_DeviceOperation(DAC960_Controller_T *Controller,
					 DAC960_V2_IOCTL_Opcode_T IOCTL_Opcode,
					 DAC960_V2_OperationDevice_T
					   OperationDevice)
{
  DAC960_Command_T *Command = DAC960_AllocateCommand(Controller);
  DAC960_V2_CommandMailbox_T *CommandMailbox = &Command->V2.CommandMailbox;
  DAC960_V2_CommandStatus_T CommandStatus;
  DAC960_V2_ClearCommand(Command);
  Command->CommandType = DAC960_ImmediateCommand;
  CommandMailbox->DeviceOperation.CommandOpcode = DAC960_V2_IOCTL;
  CommandMailbox->DeviceOperation.CommandControlBits
				 .DataTransferControllerToHost = true;
  CommandMailbox->DeviceOperation.CommandControlBits
    				 .NoAutoRequestSense = true;
  CommandMailbox->DeviceOperation.IOCTL_Opcode = IOCTL_Opcode;
  CommandMailbox->DeviceOperation.OperationDevice = OperationDevice;
  DAC960_ExecuteCommand(Command);
  CommandStatus = Command->V2.CommandStatus;
  DAC960_DeallocateCommand(Command);
  return (CommandStatus == DAC960_V2_NormalCompletion);
}
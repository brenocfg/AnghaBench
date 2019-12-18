#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_3__* ScatterGatherSegments; } ;
struct TYPE_16__ {int DataTransferControllerToHost; int NoAutoRequestSense; } ;
struct TYPE_20__ {int DataTransferSize; TYPE_4__ DataTransferMemoryAddress; int /*<<< orphan*/  IOCTL_Opcode; scalar_t__ ControllerNumber; TYPE_1__ CommandControlBits; int /*<<< orphan*/  CommandOpcode; } ;
struct TYPE_22__ {TYPE_5__ ControllerInfo; } ;
struct TYPE_21__ {scalar_t__ CommandStatus; TYPE_7__ CommandMailbox; } ;
struct TYPE_24__ {TYPE_6__ V2; int /*<<< orphan*/  CommandType; } ;
struct TYPE_17__ {int /*<<< orphan*/  NewControllerInformationDMA; } ;
struct TYPE_23__ {TYPE_2__ V2; } ;
struct TYPE_18__ {int SegmentByteCount; int /*<<< orphan*/  SegmentDataPointer; } ;
typedef  int /*<<< orphan*/  DAC960_V2_ControllerInfo_T ;
typedef  scalar_t__ DAC960_V2_CommandStatus_T ;
typedef  TYPE_7__ DAC960_V2_CommandMailbox_T ;
typedef  TYPE_8__ DAC960_Controller_T ;
typedef  TYPE_9__ DAC960_Command_T ;

/* Variables and functions */
 TYPE_9__* DAC960_AllocateCommand (TYPE_8__*) ; 
 int /*<<< orphan*/  DAC960_DeallocateCommand (TYPE_9__*) ; 
 int /*<<< orphan*/  DAC960_ExecuteCommand (TYPE_9__*) ; 
 int /*<<< orphan*/  DAC960_ImmediateCommand ; 
 int /*<<< orphan*/  DAC960_V2_ClearCommand (TYPE_9__*) ; 
 int /*<<< orphan*/  DAC960_V2_GetControllerInfo ; 
 int /*<<< orphan*/  DAC960_V2_IOCTL ; 
 scalar_t__ DAC960_V2_NormalCompletion ; 

__attribute__((used)) static bool DAC960_V2_NewControllerInfo(DAC960_Controller_T *Controller)
{
  DAC960_Command_T *Command = DAC960_AllocateCommand(Controller);
  DAC960_V2_CommandMailbox_T *CommandMailbox = &Command->V2.CommandMailbox;
  DAC960_V2_CommandStatus_T CommandStatus;
  DAC960_V2_ClearCommand(Command);
  Command->CommandType = DAC960_ImmediateCommand;
  CommandMailbox->ControllerInfo.CommandOpcode = DAC960_V2_IOCTL;
  CommandMailbox->ControllerInfo.CommandControlBits
				.DataTransferControllerToHost = true;
  CommandMailbox->ControllerInfo.CommandControlBits
				.NoAutoRequestSense = true;
  CommandMailbox->ControllerInfo.DataTransferSize = sizeof(DAC960_V2_ControllerInfo_T);
  CommandMailbox->ControllerInfo.ControllerNumber = 0;
  CommandMailbox->ControllerInfo.IOCTL_Opcode = DAC960_V2_GetControllerInfo;
  CommandMailbox->ControllerInfo.DataTransferMemoryAddress
				.ScatterGatherSegments[0]
				.SegmentDataPointer =
    	Controller->V2.NewControllerInformationDMA;
  CommandMailbox->ControllerInfo.DataTransferMemoryAddress
				.ScatterGatherSegments[0]
				.SegmentByteCount =
    CommandMailbox->ControllerInfo.DataTransferSize;
  DAC960_ExecuteCommand(Command);
  CommandStatus = Command->V2.CommandStatus;
  DAC960_DeallocateCommand(Command);
  return (CommandStatus == DAC960_V2_NormalCompletion);
}
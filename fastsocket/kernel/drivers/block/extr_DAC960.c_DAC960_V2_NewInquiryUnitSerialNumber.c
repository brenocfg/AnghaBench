#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ CommandStatus; int /*<<< orphan*/  CommandMailbox; } ;
struct TYPE_8__ {TYPE_1__ V2; int /*<<< orphan*/  CommandType; } ;
typedef  scalar_t__ DAC960_V2_CommandStatus_T ;
typedef  int /*<<< orphan*/  DAC960_V2_CommandMailbox_T ;
typedef  int /*<<< orphan*/  DAC960_Controller_T ;
typedef  TYPE_2__ DAC960_Command_T ;

/* Variables and functions */
 TYPE_2__* DAC960_AllocateCommand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DAC960_DeallocateCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  DAC960_ExecuteCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  DAC960_ImmediateCommand ; 
 int /*<<< orphan*/  DAC960_V2_ClearCommand (TYPE_2__*) ; 
 int /*<<< orphan*/  DAC960_V2_ConstructNewUnitSerialNumber (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ DAC960_V2_NormalCompletion ; 

__attribute__((used)) static bool DAC960_V2_NewInquiryUnitSerialNumber(DAC960_Controller_T *Controller,
			int Channel, int TargetID, int LogicalUnit)
{
      DAC960_Command_T *Command;
      DAC960_V2_CommandMailbox_T *CommandMailbox;
      DAC960_V2_CommandStatus_T CommandStatus;

      Command = DAC960_AllocateCommand(Controller);
      CommandMailbox = &Command->V2.CommandMailbox;
      DAC960_V2_ClearCommand(Command);
      Command->CommandType = DAC960_ImmediateCommand;

      DAC960_V2_ConstructNewUnitSerialNumber(Controller, CommandMailbox,
			Channel, TargetID, LogicalUnit);

      DAC960_ExecuteCommand(Command);
      CommandStatus = Command->V2.CommandStatus;
      DAC960_DeallocateCommand(Command);
      return (CommandStatus == DAC960_V2_NormalCompletion);
}
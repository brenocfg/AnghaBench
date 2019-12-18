#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  BusAddress; int /*<<< orphan*/  CommandOpcode; } ;
struct TYPE_13__ {TYPE_2__ Type3; } ;
struct TYPE_10__ {TYPE_4__ CommandMailbox; } ;
struct TYPE_15__ {int /*<<< orphan*/  CommandType; TYPE_1__ V1; TYPE_5__* Controller; } ;
struct TYPE_12__ {int /*<<< orphan*/  NewEnquiryDMA; } ;
struct TYPE_14__ {TYPE_3__ V1; } ;
typedef  TYPE_4__ DAC960_V1_CommandMailbox_T ;
typedef  TYPE_5__ DAC960_Controller_T ;
typedef  TYPE_6__ DAC960_Command_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_MonitoringCommand ; 
 int /*<<< orphan*/  DAC960_QueueCommand (TYPE_6__*) ; 
 int /*<<< orphan*/  DAC960_V1_ClearCommand (TYPE_6__*) ; 
 int /*<<< orphan*/  DAC960_V1_Enquiry ; 

__attribute__((used)) static void DAC960_V1_QueueMonitoringCommand(DAC960_Command_T *Command)
{
  DAC960_Controller_T *Controller = Command->Controller;
  DAC960_V1_CommandMailbox_T *CommandMailbox = &Command->V1.CommandMailbox;
  DAC960_V1_ClearCommand(Command);
  Command->CommandType = DAC960_MonitoringCommand;
  CommandMailbox->Type3.CommandOpcode = DAC960_V1_Enquiry;
  CommandMailbox->Type3.BusAddress = Controller->V1.NewEnquiryDMA;
  DAC960_QueueCommand(Command);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ CommandStatus; int /*<<< orphan*/  CommandMailbox; } ;
struct TYPE_5__ {TYPE_1__ V2; } ;
typedef  int /*<<< orphan*/  DAC960_V2_CommandMailbox_T ;
typedef  TYPE_2__ DAC960_Command_T ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void DAC960_V2_ClearCommand(DAC960_Command_T *Command)
{
  DAC960_V2_CommandMailbox_T *CommandMailbox = &Command->V2.CommandMailbox;
  memset(CommandMailbox, 0, sizeof(DAC960_V2_CommandMailbox_T));
  Command->V2.CommandStatus = 0;
}
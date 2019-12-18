#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int LogicalDriveNumber; } ;
struct TYPE_6__ {TYPE_1__ LD; } ;
struct TYPE_7__ {int* Bytes; TYPE_2__ Type5; } ;
typedef  TYPE_3__ DAC960_V1_CommandMailbox_T ;

/* Variables and functions */

__attribute__((used)) static inline
void DAC960_PD_To_P_TranslateReadWriteCommand(DAC960_V1_CommandMailbox_T
					      *CommandMailbox)
{
  int LogicalDriveNumber = CommandMailbox->Type5.LD.LogicalDriveNumber;
  CommandMailbox->Bytes[3] &= 0x7;
  CommandMailbox->Bytes[3] |= CommandMailbox->Bytes[7] << 6;
  CommandMailbox->Bytes[7] = LogicalDriveNumber;
}
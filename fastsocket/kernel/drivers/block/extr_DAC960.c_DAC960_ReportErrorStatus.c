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
struct TYPE_5__ {int DriveSpinUpMessageDisplayed; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_Error (char*,TYPE_1__*,...) ; 
 int /*<<< orphan*/  DAC960_Notice (char*,TYPE_1__*,...) ; 

__attribute__((used)) static bool DAC960_ReportErrorStatus(DAC960_Controller_T *Controller,
					unsigned char ErrorStatus,
					unsigned char Parameter0,
					unsigned char Parameter1)
{
  switch (ErrorStatus)
    {
    case 0x00:
      DAC960_Notice("Physical Device %d:%d Not Responding\n",
		    Controller, Parameter1, Parameter0);
      break;
    case 0x08:
      if (Controller->DriveSpinUpMessageDisplayed) break;
      DAC960_Notice("Spinning Up Drives\n", Controller);
      Controller->DriveSpinUpMessageDisplayed = true;
      break;
    case 0x30:
      DAC960_Notice("Configuration Checksum Error\n", Controller);
      break;
    case 0x60:
      DAC960_Notice("Mirror Race Recovery Failed\n", Controller);
      break;
    case 0x70:
      DAC960_Notice("Mirror Race Recovery In Progress\n", Controller);
      break;
    case 0x90:
      DAC960_Notice("Physical Device %d:%d COD Mismatch\n",
		    Controller, Parameter1, Parameter0);
      break;
    case 0xA0:
      DAC960_Notice("Logical Drive Installation Aborted\n", Controller);
      break;
    case 0xB0:
      DAC960_Notice("Mirror Race On A Critical Logical Drive\n", Controller);
      break;
    case 0xD0:
      DAC960_Notice("New Controller Configuration Found\n", Controller);
      break;
    case 0xF0:
      DAC960_Error("Fatal Memory Parity Error for Controller at\n", Controller);
      return true;
    default:
      DAC960_Error("Unknown Initialization Error %02X for Controller at\n",
		   Controller, ErrorStatus);
      return true;
    }
  return false;
}
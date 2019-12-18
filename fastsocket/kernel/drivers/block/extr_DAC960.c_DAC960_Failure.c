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
struct TYPE_4__ {scalar_t__ IO_Address; int /*<<< orphan*/  PCI_Address; int /*<<< orphan*/  Function; int /*<<< orphan*/  Device; int /*<<< orphan*/  Bus; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_Error (char*,TYPE_1__*,...) ; 

__attribute__((used)) static bool DAC960_Failure(DAC960_Controller_T *Controller,
			      unsigned char *ErrorMessage)
{
  DAC960_Error("While configuring DAC960 PCI RAID Controller at\n",
	       Controller);
  if (Controller->IO_Address == 0)
    DAC960_Error("PCI Bus %d Device %d Function %d I/O Address N/A "
		 "PCI Address 0x%X\n", Controller,
		 Controller->Bus, Controller->Device,
		 Controller->Function, Controller->PCI_Address);
  else DAC960_Error("PCI Bus %d Device %d Function %d I/O Address "
		    "0x%X PCI Address 0x%X\n", Controller,
		    Controller->Bus, Controller->Device,
		    Controller->Function, Controller->IO_Address,
		    Controller->PCI_Address);
  DAC960_Error("%s FAILED - DETACHING\n", Controller, ErrorMessage);
  return false;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; int offset; int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {TYPE_1__ port2; TYPE_1__ port1; scalar_t__ firstPeri; } ;
struct TYPE_5__ {int SR; int* IREG; TYPE_1__* OREG; } ;
typedef  int /*<<< orphan*/  PortData_struct ;

/* Variables and functions */
 scalar_t__ LagFrameFlag ; 
 int /*<<< orphan*/  PORTDATA1 ; 
 int /*<<< orphan*/  PORTDATA2 ; 
 int /*<<< orphan*/  PerFlush (int /*<<< orphan*/ *) ; 
 TYPE_3__* SmpcInternalVars ; 
 TYPE_2__* SmpcRegs ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void SmpcINTBACKPeripheral(void) {
  int oregoffset;
  PortData_struct *port1, *port2;

  if (SmpcInternalVars->firstPeri)
    SmpcRegs->SR = 0xC0 | (SmpcRegs->IREG[1] >> 4);
  else
    SmpcRegs->SR = 0x80 | (SmpcRegs->IREG[1] >> 4);

  SmpcInternalVars->firstPeri = 0;

  /* Port Status:
  0x04 - Sega-tap is connected
  0x16 - Multi-tap is connected
  0x21-0x2F - Clock serial peripheral is connected
  0xF0 - Not Connected or Unknown Device
  0xF1 - Peripheral is directly connected */

  /* PeripheralID:
  0x02 - Digital Device Standard Format
  0x13 - Racing Device Standard Format
  0x15 - Analog Device Standard Format
  0x23 - Pointing Device Standard Format
  0x23 - Shooting Device Standard Format
  0x34 - Keyboard Device Standard Format
  0xE1 - Mega Drive 3-Button Pad
  0xE2 - Mega Drive 6-Button Pad
  0xE3 - Saturn Mouse
  0xFF - Not Connected */

  /* Special Notes(for potential future uses):

  If a peripheral is disconnected from a port, you only return 1 byte for
  that port(which is the port status 0xF0), at the next OREG you then return
  the port status of the next port.

  e.g. If Port 1 has nothing connected, and Port 2 has a controller
       connected:

  OREG0 = 0xF0
  OREG1 = 0xF1
  OREG2 = 0x02
  etc.
  */

  oregoffset=0;

  if (SmpcInternalVars->port1.size == 0 && SmpcInternalVars->port2.size == 0)
  {
     // Request data from the Peripheral Interface
     port1 = &PORTDATA1;
     port2 = &PORTDATA2;
     memcpy(&SmpcInternalVars->port1, port1, sizeof(PortData_struct));
     memcpy(&SmpcInternalVars->port2, port2, sizeof(PortData_struct));
     PerFlush(&PORTDATA1);
     PerFlush(&PORTDATA2);
     SmpcInternalVars->port1.offset = 0;
     SmpcInternalVars->port2.offset = 0;
     LagFrameFlag=0;
  }

  // Port 1
  if (SmpcInternalVars->port1.size > 0)
  {
     if ((SmpcInternalVars->port1.size-SmpcInternalVars->port1.offset) < 32)
     {
        memcpy(SmpcRegs->OREG, SmpcInternalVars->port1.data+SmpcInternalVars->port1.offset, SmpcInternalVars->port1.size-SmpcInternalVars->port1.offset);
        oregoffset += SmpcInternalVars->port1.size-SmpcInternalVars->port1.offset;
        SmpcInternalVars->port1.size = 0;
     }
     else
     {
        memcpy(SmpcRegs->OREG, SmpcInternalVars->port1.data, 32);
        oregoffset += 32;
        SmpcInternalVars->port1.offset += 32;
     }
  }
  // Port 2
  if (SmpcInternalVars->port2.size > 0 && oregoffset < 32)
  {
     if ((SmpcInternalVars->port2.size-SmpcInternalVars->port2.offset) < (32 - oregoffset))
     {
        memcpy(SmpcRegs->OREG + oregoffset, SmpcInternalVars->port2.data+SmpcInternalVars->port2.offset, SmpcInternalVars->port2.size-SmpcInternalVars->port2.offset);
        SmpcInternalVars->port2.size = 0;
     }
     else
     {
        memcpy(SmpcRegs->OREG + oregoffset, SmpcInternalVars->port2.data, 32 - oregoffset);
        SmpcInternalVars->port2.offset += 32 - oregoffset;
     }
  }

/*
  Use this as a reference for implementing other peripherals
  // Port 1
  SmpcRegs->OREG[0] = 0xF1; //Port Status(Directly Connected)
  SmpcRegs->OREG[1] = 0xE3; //PeripheralID(Shuttle Mouse)
  SmpcRegs->OREG[2] = 0x00; //First Data
  SmpcRegs->OREG[3] = 0x00; //Second Data
  SmpcRegs->OREG[4] = 0x00; //Third Data

  // Port 2
  SmpcRegs->OREG[5] = 0xF0; //Port Status(Not Connected)
*/
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int VBR; scalar_t__* R; scalar_t__ PC; } ;
struct TYPE_11__ {TYPE_4__ regs; } ;
struct TYPE_10__ {int IsSSH2Running; scalar_t__ emulatebios; } ;

/* Variables and functions */
 scalar_t__ Cs2GetSlaveStackAdress () ; 
 TYPE_2__* CurrentSH2 ; 
 TYPE_2__* MSH2 ; 
 scalar_t__ MappedMemoryReadLong (int) ; 
 int /*<<< orphan*/  MappedMemoryWriteLong (int,int) ; 
 int /*<<< orphan*/  MappedMemoryWriteWord (int,int) ; 
 int /*<<< orphan*/  SH2GetRegisters (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SH2PowerOn (TYPE_2__*) ; 
 int /*<<< orphan*/  SH2SetRegisters (TYPE_2__*,TYPE_4__*) ; 
 TYPE_2__* SSH2 ; 
 TYPE_1__ yabsys ; 

void YabauseStartSlave(void) {
   if (yabsys.emulatebios)
   {
      CurrentSH2 = SSH2;
      MappedMemoryWriteLong(0xFFFFFFE0, 0xA55A03F1); // BCR1
      MappedMemoryWriteLong(0xFFFFFFE4, 0xA55A00FC); // BCR2
      MappedMemoryWriteLong(0xFFFFFFE8, 0xA55A5555); // WCR
      MappedMemoryWriteLong(0xFFFFFFEC, 0xA55A0070); // MCR

      MappedMemoryWriteWord(0xFFFFFEE0, 0x0000); // ICR
      MappedMemoryWriteWord(0xFFFFFEE2, 0x0000); // IPRA
      MappedMemoryWriteWord(0xFFFFFE60, 0x0F00); // VCRWDT
      MappedMemoryWriteWord(0xFFFFFE62, 0x6061); // VCRA
      MappedMemoryWriteWord(0xFFFFFE64, 0x6263); // VCRB
      MappedMemoryWriteWord(0xFFFFFE66, 0x6465); // VCRC
      MappedMemoryWriteWord(0xFFFFFE68, 0x6600); // VCRD
      MappedMemoryWriteWord(0xFFFFFEE4, 0x6869); // VCRWDT
      MappedMemoryWriteLong(0xFFFFFFA8, 0x0000006C); // VCRDMA1
      MappedMemoryWriteLong(0xFFFFFFA0, 0x0000006D); // VCRDMA0
      MappedMemoryWriteLong(0xFFFFFF0C, 0x0000006E); // VCRDIV
      MappedMemoryWriteLong(0xFFFFFE10, 0x00000081); // TIER
      CurrentSH2 = MSH2;

      SH2GetRegisters(SSH2, &SSH2->regs);
      SSH2->regs.R[15] = Cs2GetSlaveStackAdress();
      SSH2->regs.VBR = 0x06000400;
      SSH2->regs.PC = MappedMemoryReadLong(0x06000250);
      if (MappedMemoryReadLong(0x060002AC) != 0)
         SSH2->regs.R[15] = MappedMemoryReadLong(0x060002AC);
      SH2SetRegisters(SSH2, &SSH2->regs);
   }
   else
      SH2PowerOn(SSH2);

   yabsys.IsSSH2Running = 1;
}
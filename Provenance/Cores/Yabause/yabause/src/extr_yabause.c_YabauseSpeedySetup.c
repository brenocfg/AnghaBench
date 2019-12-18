#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_19__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  Vdp2 ;
struct TYPE_30__ {int all; } ;
struct TYPE_29__ {int all; } ;
struct TYPE_28__ {int all; } ;
struct TYPE_27__ {int all; } ;
struct TYPE_34__ {int TVMD; int TVSTAT; int CYCA0L; int CYCA0U; int CYCA1L; int CYCA1U; int CYCB0L; int CYCB0U; int CYCB1L; int CYCB1U; int BGON; int PNCN0; int MPABN0; int MPCDN0; int BKTAL; int SPCTL; int PRINA; int CLOFEN; int COAR; int COAG; int COAB; TYPE_4__ ZMYN1; TYPE_3__ ZMXN1; TYPE_2__ ZMYN0; TYPE_1__ ZMXN0; } ;
struct TYPE_33__ {scalar_t__ emulatebios; } ;
struct TYPE_32__ {int all; } ;
struct TYPE_31__ {int HIRQ; int CR1; int CR2; int CR3; scalar_t__ CR4; } ;
struct TYPE_26__ {int status; int options; int repcnt; int ctrladdr; int track; int index; int FAD; int satauth; TYPE_5__ reg; scalar_t__ isdiskchanged; } ;
struct TYPE_25__ {int* R; int GBR; int VBR; int MACH; int MACL; int PR; TYPE_6__ SR; } ;
struct TYPE_24__ {TYPE_15__ regs; } ;
struct TYPE_23__ {int D0EN; int IST; int AIACK; int ASR0; int ASR1; int AREF; int RSEL; scalar_t__ D2AD; scalar_t__ D1AD; } ;
struct TYPE_22__ {scalar_t__ resd; } ;
struct TYPE_21__ {int COMREG; } ;
struct TYPE_20__ {int EDSR; int localX; int localY; int systemclipX2; int systemclipY2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BiosInit () ; 
 TYPE_19__* Cs2Area ; 
 TYPE_14__* MSH2 ; 
 int MappedMemoryReadLong (int) ; 
 int /*<<< orphan*/  MappedMemoryWriteLong (int,int) ; 
 int /*<<< orphan*/  SH2GetRegisters (TYPE_14__*,TYPE_15__*) ; 
 int /*<<< orphan*/  SH2SetRegisters (TYPE_14__*,TYPE_15__*) ; 
 TYPE_13__* ScuRegs ; 
 TYPE_12__* SmpcInternalVars ; 
 TYPE_11__* SmpcRegs ; 
 TYPE_10__* Vdp1Regs ; 
 TYPE_8__* Vdp2Regs ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 TYPE_7__ yabsys ; 

void YabauseSpeedySetup(void)
{
   u32 data;
   int i;

   if (yabsys.emulatebios)
      BiosInit();
   else
   {
      // Setup the vector table area, etc.(all bioses have it at 0x00000600-0x00000810)
      for (i = 0; i < 0x210; i+=4)
      {
         data = MappedMemoryReadLong(0x00000600+i);
         MappedMemoryWriteLong(0x06000000+i, data);
      }

      // Setup the bios function pointers, etc.(all bioses have it at 0x00000820-0x00001100)
      for (i = 0; i < 0x8E0; i+=4)
      {
         data = MappedMemoryReadLong(0x00000820+i);
         MappedMemoryWriteLong(0x06000220+i, data);
      }

      // I'm not sure this is really needed
      for (i = 0; i < 0x700; i+=4)
      {
         data = MappedMemoryReadLong(0x00001100+i);
         MappedMemoryWriteLong(0x06001100+i, data);
      }

      // Fix some spots in 0x06000210-0x0600032C area
      MappedMemoryWriteLong(0x06000234, 0x000002AC);
      MappedMemoryWriteLong(0x06000238, 0x000002BC);
      MappedMemoryWriteLong(0x0600023C, 0x00000350);
      MappedMemoryWriteLong(0x06000240, 0x32524459);
      MappedMemoryWriteLong(0x0600024C, 0x00000000);
      MappedMemoryWriteLong(0x06000268, MappedMemoryReadLong(0x00001344));
      MappedMemoryWriteLong(0x0600026C, MappedMemoryReadLong(0x00001348));
      MappedMemoryWriteLong(0x0600029C, MappedMemoryReadLong(0x00001354));
      MappedMemoryWriteLong(0x060002C4, MappedMemoryReadLong(0x00001104));
      MappedMemoryWriteLong(0x060002C8, MappedMemoryReadLong(0x00001108));
      MappedMemoryWriteLong(0x060002CC, MappedMemoryReadLong(0x0000110C));
      MappedMemoryWriteLong(0x060002D0, MappedMemoryReadLong(0x00001110));
      MappedMemoryWriteLong(0x060002D4, MappedMemoryReadLong(0x00001114));
      MappedMemoryWriteLong(0x060002D8, MappedMemoryReadLong(0x00001118));
      MappedMemoryWriteLong(0x060002DC, MappedMemoryReadLong(0x0000111C));
      MappedMemoryWriteLong(0x06000328, 0x000004C8);
      MappedMemoryWriteLong(0x0600032C, 0x00001800);

      // Fix SCU interrupts
      for (i = 0; i < 0x80; i+=4)
         MappedMemoryWriteLong(0x06000A00+i, 0x0600083C);
   }

   // Set the cpu's, etc. to sane states

   // Set CD block to a sane state
   Cs2Area->reg.HIRQ = 0xFC1;
   Cs2Area->isdiskchanged = 0;
   Cs2Area->reg.CR1 = (Cs2Area->status << 8) | ((Cs2Area->options & 0xF) << 4) | (Cs2Area->repcnt & 0xF);
   Cs2Area->reg.CR2 = (Cs2Area->ctrladdr << 8) | Cs2Area->track;
   Cs2Area->reg.CR3 = (Cs2Area->index << 8) | ((Cs2Area->FAD >> 16) & 0xFF);
   Cs2Area->reg.CR4 = (u16) Cs2Area->FAD;
   Cs2Area->satauth = 4;

   // Set Master SH2 registers accordingly
   SH2GetRegisters(MSH2, &MSH2->regs);
   for (i = 0; i < 15; i++)
      MSH2->regs.R[i] = 0x00000000;
   MSH2->regs.R[15] = 0x06002000;
   MSH2->regs.SR.all = 0x00000000;
   MSH2->regs.GBR = 0x00000000;
   MSH2->regs.VBR = 0x06000000;
   MSH2->regs.MACH = 0x00000000;
   MSH2->regs.MACL = 0x00000000;
   MSH2->regs.PR = 0x00000000;
   SH2SetRegisters(MSH2, &MSH2->regs);

   // Set SCU registers to sane states
   ScuRegs->D1AD = ScuRegs->D2AD = 0;
   ScuRegs->D0EN = 0x101;
   ScuRegs->IST = 0x2006;
   ScuRegs->AIACK = 0x1;
   ScuRegs->ASR0 = ScuRegs->ASR1 = 0x1FF01FF0;
   ScuRegs->AREF = 0x1F;
   ScuRegs->RSEL = 0x1;

   // Set SMPC registers to sane states
   SmpcRegs->COMREG = 0x10;
   SmpcInternalVars->resd = 0;

   // Set VDP1 registers to sane states
   Vdp1Regs->EDSR = 3;
   Vdp1Regs->localX = 160;
   Vdp1Regs->localY = 112;
   Vdp1Regs->systemclipX2 = 319;
   Vdp1Regs->systemclipY2 = 223;

   // Set VDP2 registers to sane states
   memset(Vdp2Regs, 0, sizeof(Vdp2));
   Vdp2Regs->TVMD = 0x8000;
   Vdp2Regs->TVSTAT = 0x020A;
   Vdp2Regs->CYCA0L = 0x0F44;
   Vdp2Regs->CYCA0U = 0xFFFF;
   Vdp2Regs->CYCA1L = 0xFFFF;
   Vdp2Regs->CYCA1U = 0xFFFF;
   Vdp2Regs->CYCB0L = 0xFFFF;
   Vdp2Regs->CYCB0U = 0xFFFF;
   Vdp2Regs->CYCB1L = 0xFFFF;
   Vdp2Regs->CYCB1U = 0xFFFF;
   Vdp2Regs->BGON = 0x0001;
   Vdp2Regs->PNCN0 = 0x8000;
   Vdp2Regs->MPABN0 = 0x0303;
   Vdp2Regs->MPCDN0 = 0x0303;
   Vdp2Regs->ZMXN0.all = 0x00010000;
   Vdp2Regs->ZMYN0.all = 0x00010000;
   Vdp2Regs->ZMXN1.all = 0x00010000;
   Vdp2Regs->ZMYN1.all = 0x00010000;
   Vdp2Regs->BKTAL = 0x4000;
   Vdp2Regs->SPCTL = 0x0020;
   Vdp2Regs->PRINA = 0x0007;
   Vdp2Regs->CLOFEN = 0x0001;
   Vdp2Regs->COAR = 0x0200;
   Vdp2Regs->COAG = 0x0200;
   Vdp2Regs->COAB = 0x0200;
}
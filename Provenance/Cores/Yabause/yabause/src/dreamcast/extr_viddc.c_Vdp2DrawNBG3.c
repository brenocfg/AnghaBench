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
struct TYPE_5__ {int enable; int transparencyenable; int specialprimode; int colornumber; int mapwh; int planew; int planeh; int x; int y; int patterndatasize; int patternwh; int pagewh; int cellw; int cellh; int supplementdata; int auxmode; int alpha; int coloroffset; int cor; int cog; int cob; int coordincx; int coordincy; void (* PlaneAddr ) (void*,int) ;int /*<<< orphan*/  priority; int /*<<< orphan*/ * PostPixelFetchCalc; } ;
typedef  TYPE_1__ vdp2draw_struct ;
struct TYPE_7__ {int disptoggle; } ;
struct TYPE_6__ {int BGON; int SFPRMD; int CHCTLB; int PLSZ; int SCXN3; int SCYN3; int PNCN3; int CCCTL; int CCRNB; int CRAOFA; int CLOFEN; int CLOFSL; int COBR; int COBG; int COBB; int COAR; int COAG; int COAB; } ;

/* Variables and functions */
 int /*<<< orphan*/  DoColorCalc ; 
 int /*<<< orphan*/  DoColorCalcWithColorOffset ; 
 int /*<<< orphan*/  DoColorOffset ; 
 int /*<<< orphan*/  DoNothing ; 
 int /*<<< orphan*/  Vdp2DrawMap (TYPE_1__*) ; 
 TYPE_3__ Vdp2External ; 
 int /*<<< orphan*/  Vdp2NBG3PlaneAddr ; 
 TYPE_2__* Vdp2Regs ; 
 int /*<<< orphan*/  nbg3priority ; 

__attribute__((used)) static int Vdp2DrawNBG3(void)
{
   vdp2draw_struct info;

   info.enable = Vdp2Regs->BGON & 0x8;

   if (!(info.enable & Vdp2External.disptoggle))
       return 0;

   info.transparencyenable = !(Vdp2Regs->BGON & 0x800);
   info.specialprimode = (Vdp2Regs->SFPRMD >> 6) & 0x3;

   info.colornumber = (Vdp2Regs->CHCTLB & 0x20) >> 5;

   info.mapwh = 2;

   switch((Vdp2Regs->PLSZ & 0xC0) >> 6)
   {
      case 0:
         info.planew = info.planeh = 1;
         break;
      case 1:
         info.planew = 2;
         info.planeh = 1;
         break;
      case 3:
         info.planew = info.planeh = 2;
         break;
      default: // Not sure what 0x2 does
         info.planew = info.planeh = 1;
         break;
   }
   info.x = - ((Vdp2Regs->SCXN3 & 0x7FF) % (512 * info.planew));
   info.y = - ((Vdp2Regs->SCYN3 & 0x7FF) % (512 * info.planeh));

   if(Vdp2Regs->PNCN3 & 0x8000)
      info.patterndatasize = 1;
   else
      info.patterndatasize = 2;

   if(Vdp2Regs->CHCTLB & 0x10)
      info.patternwh = 2;
   else
      info.patternwh = 1;

   info.pagewh = 64/info.patternwh;
   info.cellw = info.cellh = 8;
   info.supplementdata = Vdp2Regs->PNCN3 & 0x3FF;
   info.auxmode = (Vdp2Regs->PNCN3 & 0x4000) >> 14;

   if (Vdp2Regs->CCCTL & 0x8)
      info.alpha = ((~Vdp2Regs->CCRNB & 0x1F00) >> 5) + 0x7;
   else
      info.alpha = 0xFF;

   info.coloroffset = (Vdp2Regs->CRAOFA & 0x7000) >> 4;

   if (Vdp2Regs->CLOFEN & 0x8)
   {
      // color offset enable
      if (Vdp2Regs->CLOFSL & 0x8)
      {
         // color offset B
         info.cor = Vdp2Regs->COBR & 0xFF;
         if (Vdp2Regs->COBR & 0x100)
            info.cor |= 0xFFFFFF00;

         info.cog = Vdp2Regs->COBG & 0xFF;
         if (Vdp2Regs->COBG & 0x100)
            info.cog |= 0xFFFFFF00;

         info.cob = Vdp2Regs->COBB & 0xFF;
         if (Vdp2Regs->COBB & 0x100)
            info.cob |= 0xFFFFFF00;
      }
      else
      {
         // color offset A
         info.cor = Vdp2Regs->COAR & 0xFF;
         if (Vdp2Regs->COAR & 0x100)
            info.cor |= 0xFFFFFF00;

         info.cog = Vdp2Regs->COAG & 0xFF;
         if (Vdp2Regs->COAG & 0x100)
            info.cog |= 0xFFFFFF00;

         info.cob = Vdp2Regs->COAB & 0xFF;
         if (Vdp2Regs->COAB & 0x100)
            info.cob |= 0xFFFFFF00;
      }

      if (Vdp2Regs->CCCTL & 0x8)
         info.PostPixelFetchCalc = &DoColorCalcWithColorOffset;
      else
         info.PostPixelFetchCalc = &DoColorOffset;
   }
   else // color offset disable
   {
      if (Vdp2Regs->CCCTL & 0x8)
         info.PostPixelFetchCalc = &DoColorCalc;
      else
         info.PostPixelFetchCalc = &DoNothing;
   }

   info.coordincx = info.coordincy = 1;

   info.priority = nbg3priority;
   info.PlaneAddr = (void (*)(void *, int))&Vdp2NBG3PlaneAddr;

   Vdp2DrawMap(&info);

   return 1;
}
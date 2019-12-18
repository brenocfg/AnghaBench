#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int CHCTLB; int BGON; int RPMD; int KTCTL; int WCTLD; int MPOFR; int PNCR; int PLSZ; int MPABRA; int MPCDRA; int MPEFRA; int MPGHRA; int MPIJRA; int MPKLRA; int MPMNRA; int MPOPRA; int MPABRB; int MPCDRB; int MPEFRB; int MPGHRB; int MPIJRB; int MPKLRB; int MPMNRB; int MPOPRB; int CRAOFB; int SFPRMD; int PRIR; int CCRR; int SFCCMD; int /*<<< orphan*/  WCTLC; int /*<<< orphan*/  BMPNB; } ;

/* Variables and functions */
 char* AddBitmapInfoString (char*,int,int /*<<< orphan*/ ,int) ; 
 char* AddBppString (char*,int) ; 
 char* AddColorCalcInfo (char*,int,int,int,int) ; 
 char* AddColorOffsetInfo (char*,int) ; 
 char* AddMapInfo (char*,int,int,int,int,int,int*) ; 
 char* AddMosaicString (char*,int) ; 
 char* AddSpecialPriorityInfo (char*,int) ; 
 int /*<<< orphan*/  AddString (char*,char*,...) ; 
 char* AddWindowInfoString (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CalcWindowCoordinates (int,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  Vdp2GetPlaneSize (int,int*,int*) ; 
 TYPE_1__* Vdp2Regs ; 

void Vdp2DebugStatsRBG0(char *outstring, int *isenabled)
{
   int patternwh=((Vdp2Regs->CHCTLB & 0x100) >> 8) + 1;
   u8 map[16];
   int hstart, vstart, hend, vend;

   if (Vdp2Regs->BGON & 0x10)
   {
      // enabled
      int rotatenum=0;
      int coeftbl=0, coefmode=0;

      *isenabled = 1;

      // Which Rotation Parameter is being used
      switch (Vdp2Regs->RPMD & 0x3)
      {
         case 0:
            // Parameter A
            rotatenum = 0;
            coeftbl = Vdp2Regs->KTCTL & 0x1;
            coefmode = (Vdp2Regs->KTCTL >> 2) & 0x3;
            AddString(outstring, "Using Parameter %C\r\n", 'A' + rotatenum);
            break;
         case 1:
            // Parameter B
            rotatenum = 1;
            coeftbl = Vdp2Regs->KTCTL & 0x100;
            coefmode = (Vdp2Regs->KTCTL >> 10) & 0x3;
            AddString(outstring, "Using Parameter B\r\n");
            break;
         case 2:
            // Parameter A+B switched via coefficients
            AddString(outstring, "Parameter A/B switched via coefficients\r\n");
            break;
         case 3:
            // Parameter A+B switched via rotation parameter window
            AddString(outstring, "Parameter A/B switched parameter window\r\n");
            if (Vdp2Regs->WCTLD & 0x2)
            {
               AddString(outstring, "Rotation Window 0 Enabled\r\n");
               CalcWindowCoordinates(0, &hstart, &vstart, &hend, &vend);
               AddString(outstring, "Horizontal start = %d\r\n", hstart);
               AddString(outstring, "Vertical start = %d\r\n", vstart);
               AddString(outstring, "Horizontal end = %d\r\n", hend);
               AddString(outstring, "Vertical end = %d\r\n", vend);
            }
            else if (Vdp2Regs->WCTLD & 0x4)
            {
               AddString(outstring, "Rotation Window 1 Enabled\r\n");
               CalcWindowCoordinates(1, &hstart, &vstart, &hend, &vend);
               AddString(outstring, "Horizontal start = %d\r\n", hstart);
               AddString(outstring, "Vertical start = %d\r\n", vstart);
               AddString(outstring, "Horizontal end = %d\r\n", hend);
               AddString(outstring, "Vertical end = %d\r\n", vend);
            }
            break;
      }

      if (coeftbl)
      {
         AddString(outstring, "Coefficient Table Enabled(Mode %d)\r\n", coefmode);
      }

      // Mosaic
      outstring = AddMosaicString(outstring, 0x10);

      // BPP
      outstring = AddBppString(outstring, (Vdp2Regs->CHCTLB >> 12) & 0x7);

      // Bitmap or Tile mode?
      if (Vdp2Regs->CHCTLB & 0x200)
      {
         // Bitmap mode
         if (rotatenum == 0)
         {
            // Parameter A
            outstring = AddBitmapInfoString(outstring, (Vdp2Regs->CHCTLB & 0x400) >> 10, Vdp2Regs->BMPNB, Vdp2Regs->MPOFR);
         }
         else
         {
            // Parameter B
            outstring = AddBitmapInfoString(outstring, (Vdp2Regs->CHCTLB & 0x400) >> 10, Vdp2Regs->BMPNB, Vdp2Regs->MPOFR >> 4);
         }
      }
      else
      {
         // Tile mode
         int patterndatasize;
         u16 supplementdata=Vdp2Regs->PNCR & 0x3FF;
         int planew=0, planeh=0;

         if(Vdp2Regs->PNCR & 0x8000)
            patterndatasize = 1;
         else
            patterndatasize = 2;

         AddString(outstring, "Tile(%dH x %dV)\r\n", patternwh, patternwh);

         if (rotatenum == 0)
         {
            // Parameter A
            Vdp2GetPlaneSize((Vdp2Regs->PLSZ & 0x300) >> 8, &planew, &planeh);
         }
         else
         {
            // Parameter B
            Vdp2GetPlaneSize((Vdp2Regs->PLSZ & 0x3000) >> 8, &planew, &planeh);
         }

         AddString(outstring, "Plane Size = %dH x %dV\r\n", planew, planeh);

         // Pattern Name Control stuff
         if (patterndatasize == 2)
         {
            AddString(outstring, "Pattern Name data size = 2 words\r\n");
         }
         else
         {
            AddString(outstring, "Pattern Name data size = 1 word\r\n");
            AddString(outstring, "Character Number Supplement bit = %d\r\n", (supplementdata >> 14) & 0x1);
            AddString(outstring, "Special Priority bit = %d\r\n", (supplementdata >> 9) & 0x1);
            AddString(outstring, "Special Color Calculation bit = %d\r\n", (supplementdata >> 8) & 0x1);
            AddString(outstring, "Supplementary Palette number = %d\r\n", (supplementdata >> 5) & 0x7);
            AddString(outstring, "Supplementary Color number = %d\r\n", supplementdata & 0x1f);
         }

         if (rotatenum == 0)
         {
            // Parameter A
            map[0] = Vdp2Regs->MPABRA & 0xFF;
            map[1] = Vdp2Regs->MPABRA >> 8;
            map[2] = Vdp2Regs->MPCDRA & 0xFF;
            map[3] = Vdp2Regs->MPCDRA >> 8;
            map[4] = Vdp2Regs->MPEFRA & 0xFF;
            map[5] = Vdp2Regs->MPEFRA >> 8;
            map[6] = Vdp2Regs->MPGHRA & 0xFF;
            map[7] = Vdp2Regs->MPGHRA >> 8;
            map[8] = Vdp2Regs->MPIJRA & 0xFF;
            map[9] = Vdp2Regs->MPIJRA >> 8;
            map[10] = Vdp2Regs->MPKLRA & 0xFF;
            map[11] = Vdp2Regs->MPKLRA >> 8;
            map[12] = Vdp2Regs->MPMNRA & 0xFF;
            map[13] = Vdp2Regs->MPMNRA >> 8;
            map[14] = Vdp2Regs->MPOPRA & 0xFF;
            map[15] = Vdp2Regs->MPOPRA >> 8;
            outstring = AddMapInfo(outstring, patternwh, Vdp2Regs->PNCR, (Vdp2Regs->PLSZ >> 8) & 0x3, (Vdp2Regs->MPOFR & 0x7) << 6, 16, map);
         }
         else
         {
            // Parameter B
            map[0] = Vdp2Regs->MPABRB & 0xFF;
            map[1] = Vdp2Regs->MPABRB >> 8;
            map[2] = Vdp2Regs->MPCDRB & 0xFF;
            map[3] = Vdp2Regs->MPCDRB >> 8;
            map[4] = Vdp2Regs->MPEFRB & 0xFF;
            map[5] = Vdp2Regs->MPEFRB >> 8;
            map[6] = Vdp2Regs->MPGHRB & 0xFF;
            map[7] = Vdp2Regs->MPGHRB >> 8;
            map[8] = Vdp2Regs->MPIJRB & 0xFF;
            map[9] = Vdp2Regs->MPIJRB >> 8;
            map[10] = Vdp2Regs->MPKLRB & 0xFF;
            map[11] = Vdp2Regs->MPKLRB >> 8;
            map[12] = Vdp2Regs->MPMNRB & 0xFF;
            map[13] = Vdp2Regs->MPMNRB >> 8;
            map[14] = Vdp2Regs->MPOPRB & 0xFF;
            map[15] = Vdp2Regs->MPOPRB >> 8;
            outstring = AddMapInfo(outstring, patternwh, Vdp2Regs->PNCR, (Vdp2Regs->PLSZ >> 12) & 0x3, (Vdp2Regs->MPOFR & 0x70) << 2, 16, map);
         }

/*
         // Figure out Cell start address
         switch(patterndatasize)
         {
            case 1:
            {
               tmp = readWord(vram, addr);

               switch(auxMode)
               {
                  case 0:
                     switch(patternwh)
                     {
                        case 1:
                           charAddr = (tmp & 0x3FF) | ((supplementdata & 0x1F) << 10);
                           break;
                        case 2:
                           charAddr = ((tmp & 0x3FF) << 2) |  (supplementdata & 0x3) | ((supplementdata & 0x1C) << 10);
                           break;
                     }
                     break;
                  case 1:
                     switch(patternwh)
                     {
                        case 1:
                           charAddr = (tmp & 0xFFF) | ((supplementdata & 0x1C) << 10);
                           break;
                        case 4:
                           charAddr = ((tmp & 0xFFF) << 2) |  (supplementdata & 0x3) | ((supplementdata & 0x10) << 10);
                           break;
                     }
                     break;
               }
               break;
            }
            case 2:
            {
               unsigned short tmp1 = readWord(vram, addr);
               unsigned short tmp2 = readWord(vram, addr+2);

               charAddr = tmp2 & 0x7FFF;
               break;
            }
         }

         if (!(readWord(reg, 0x6) & 0x8000))
            charAddr &= 0x3FFF;

         charAddr *= 0x20; // selon Runik

         AddString(outstring, "Cell Data Address = %X\r\n", charAddr);
*/
      }

      // Window Control
      outstring = AddWindowInfoString(outstring, Vdp2Regs->WCTLC, 0);

      // Shadow Control here

      // Color Ram Address Offset
      AddString(outstring, "Color Ram Address Offset = %X\r\n", (Vdp2Regs->CRAOFB & 0x7) << 8);

      // Special Priority Mode
      outstring = AddSpecialPriorityInfo(outstring, Vdp2Regs->SFPRMD >> 8);

      // Color Calculation Control here

      // Special Color Calculation Mode here

      // Priority Number
      AddString(outstring, "Priority = %d\r\n", Vdp2Regs->PRIR & 0x7);

      // Color Calculation
      outstring = AddColorCalcInfo(outstring, 0x0010, 0x0001, Vdp2Regs->CCRR & 0x1F, (Vdp2Regs->SFCCMD >> 8) & 0x3);

      // Color Offset
      outstring = AddColorOffsetInfo(outstring, 0x0010);

      AddString(outstring, "Special Color Calculation %d\r\n",(Vdp2Regs->SFCCMD>>8)&0x03);
   }
   else
   {
      // disabled
      *isenabled = 0;
   }
}
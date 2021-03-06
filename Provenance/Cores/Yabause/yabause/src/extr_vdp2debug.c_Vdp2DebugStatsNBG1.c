#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_7__ {int all; } ;
struct TYPE_6__ {int all; } ;
struct TYPE_5__ {int all; } ;
struct TYPE_8__ {int SCRCTL; int CHCTLA; int BGON; int BMPNA; int MPOFN; int PNCN1; int PLSZ; int MPABN1; int MPCDN1; int SCXIN1; int SCYIN1; int ZMCTL; int WCTLA; int CRAOFA; int SFPRMD; int PRINA; int CCRNA; int SFCCMD; TYPE_3__ VCSTA; TYPE_2__ LSTA1; TYPE_1__ ZMXN1; } ;

/* Variables and functions */
 char* AddBitmapInfoString (char*,int,int,int) ; 
 char* AddBppString (char*,int) ; 
 char* AddColorCalcInfo (char*,int,int,int,int) ; 
 char* AddColorOffsetInfo (char*,int) ; 
 char* AddMapInfo (char*,int,int,int,int,int,int*) ; 
 char* AddMosaicString (char*,int) ; 
 char* AddSpecialPriorityInfo (char*,int) ; 
 int /*<<< orphan*/  AddString (char*,char*,...) ; 
 char* AddWindowInfoString (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vdp2GetPlaneSize (int,int*,int*) ; 
 TYPE_4__* Vdp2Regs ; 

void Vdp2DebugStatsNBG1(char *outstring, int *isenabled)
{
   u16 lineVerticalScrollReg = (Vdp2Regs->SCRCTL >> 8) & 0x3F;
   int isbitmap=Vdp2Regs->CHCTLA & 0x200;
   int patternwh=((Vdp2Regs->CHCTLA & 0x100) >> 8) + 1;
   u8 map[4];

   if (Vdp2Regs->BGON & 0x2)
   {
      // enabled
      *isenabled = 1;

      // Mosaic
      outstring = AddMosaicString(outstring, 0x2);

      // BPP
      outstring = AddBppString(outstring, (Vdp2Regs->CHCTLA & 0x3000) >> 12);

      // Bitmap or Tile mode?
      if (isbitmap)
      {
         // Bitmap
         outstring = AddBitmapInfoString(outstring, (Vdp2Regs->CHCTLA & 0xC00) >> 10, Vdp2Regs->BMPNA >> 8, Vdp2Regs->MPOFN >> 4);
      }
      else
      {
         int patterndatasize;
         u16 supplementdata=Vdp2Regs->PNCN1 & 0x3FF;
         int planew=0, planeh=0;

         if(Vdp2Regs->PNCN1 & 0x8000)
           patterndatasize = 1;
         else
           patterndatasize = 2;

         // Tile
         AddString(outstring, "Tile(%dH x %dV)\r\n", patternwh, patternwh);

         Vdp2GetPlaneSize((Vdp2Regs->PLSZ & 0xC) >> 2, &planew, &planeh);
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

         map[0] = Vdp2Regs->MPABN1 & 0xFF;
         map[1] = Vdp2Regs->MPABN1 >> 8;
         map[2] = Vdp2Regs->MPCDN1 & 0xFF;
         map[3] = Vdp2Regs->MPCDN1 >> 8;
         outstring = AddMapInfo(outstring, patternwh, Vdp2Regs->PNCN1, (Vdp2Regs->PLSZ & 0xC) >> 2, (Vdp2Regs->MPOFN & 0x70) << 2, 4, map);

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

/*
      // Screen scroll values
      AddString(outstring, "Screen Scroll x = %f, y = %f\r\n", (float)(reg->getLong(0x80) & 0x7FFFF00) / 65536, (float)(reg->getLong(0x84) & 0x7FFFF00) / 65536);
*/
         AddString(outstring, "Screen Scroll x = %d, y = %d\r\n", - ((Vdp2Regs->SCXIN1 & 0x7FF) % 512), - ((Vdp2Regs->SCYIN1 & 0x7FF) % 512));

      // Coordinate Increments
      AddString(outstring, "Coordinate Increments x = %f, y = %f\r\n", (float) 65536 / (Vdp2Regs->ZMXN1.all & 0x7FF00), (float) 65536 / (Vdp2Regs->ZMXN1.all & 0x7FF00));

      // Reduction Enable
      switch ((Vdp2Regs->ZMCTL >> 8) & 3)
      {
         case 1:
            AddString(outstring, "Horizontal Reduction = 1/2\r\n");
            break;
         case 2:
         case 3:
            AddString(outstring, "Horizontal Reduction = 1/4\r\n");
            break;
         default: break;
      }

      if (lineVerticalScrollReg & 0x8)
      {
         AddString(outstring, "Line Zoom X enabled\r\n");
      }

      if (lineVerticalScrollReg & 0x4)
      {
         AddString(outstring, "Line Scroll Vertical enabled\r\n");
      }

      if (lineVerticalScrollReg & 0x2)
      {
         AddString(outstring, "Line Scroll Horizontal enabled\r\n");
      }

      if (lineVerticalScrollReg & 0x6)
      {
         AddString(outstring, "Line Scroll Enabled\r\n");
         AddString(outstring, "Line Scroll Table Address = %08X\r\n", (int)(0x05E00000 + ((Vdp2Regs->LSTA1.all & 0x7FFFE) << 1)));
         switch (lineVerticalScrollReg >> 4)
         {
            case 0:
               AddString(outstring, "Line Scroll Interval = Each Line\r\n");
               break;
            case 1:
               AddString(outstring, "Line Scroll Interval = Every 2 Lines\r\n");
               break;
            case 2:
               AddString(outstring, "Line Scroll Interval = Every 4 Lines\r\n");
               break;
            case 3:
               AddString(outstring, "Line Scroll Interval = Every 8 Lines\r\n");
               break;
         }
      }

      if (lineVerticalScrollReg & 0x1)
      {
         AddString(outstring, "Vertical Cell Scroll enabled\r\n");
         AddString(outstring, "Vertical Cell Scroll Table Address = %08X\r\n", (int)(0x05E00000 + ((Vdp2Regs->VCSTA.all & 0x7FFFE) << 1)));
      }

      // Window Control
      outstring = AddWindowInfoString(outstring, Vdp2Regs->WCTLA >> 8, 0);

      // Shadow Control here

      // Color Ram Address Offset
      AddString(outstring, "Color Ram Address Offset = %X\r\n", (Vdp2Regs->CRAOFA & 0x70) << 4);

      // Special Priority Mode
      outstring = AddSpecialPriorityInfo(outstring, Vdp2Regs->SFPRMD >> 2);

      // Color Calculation Control here

      // Special Color Calculation Mode here

      // Priority Number
      AddString(outstring, "Priority = %d\r\n", (Vdp2Regs->PRINA >> 8) & 0x7);

      // Color Calculation
      outstring = AddColorCalcInfo(outstring, 0x0002, 0x0004, (Vdp2Regs->CCRNA >> 8) & 0x1F, (Vdp2Regs->SFCCMD >> 2) & 0x3);

      // Color Offset
      outstring = AddColorOffsetInfo(outstring, 0x0002);

      AddString(outstring, "Special Color Calculation %d\r\n",(Vdp2Regs->SFCCMD>>2)&0x03);
   }
   else
     // disabled
     *isenabled = 0;
}
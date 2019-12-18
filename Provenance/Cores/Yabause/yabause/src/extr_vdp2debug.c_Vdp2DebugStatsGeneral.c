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
typedef  int u8 ;
struct TYPE_4__ {int U; } ;
struct TYPE_5__ {int all; TYPE_1__ part; } ;
struct TYPE_6__ {int TVMD; int TVSTAT; int EXTEN; int BKTAU; int BKTAL; int SPCTL; int SDCTL; int WCTLC; int CRAOFB; int CCCTL; TYPE_2__ LCTA; int /*<<< orphan*/  VCNT; int /*<<< orphan*/  HCNT; int /*<<< orphan*/  CCRSA; int /*<<< orphan*/  PRISA; } ;

/* Variables and functions */
 char* AddColorOffsetInfo (char*,int) ; 
 int /*<<< orphan*/  AddString (char*,char*,...) ; 
 char* AddWindowInfoString (char*,int,int) ; 
 TYPE_3__* Vdp2Regs ; 

void Vdp2DebugStatsGeneral(char *outstring, int *isenabled)
{
   u8 *sprprilist = (u8 *)&Vdp2Regs->PRISA;
   u8 *sprccrlist = (u8 *)&Vdp2Regs->CCRSA;
   int i;

   if (Vdp2Regs->TVMD & 0x8000)
   {
      // TVMD stuff
      AddString(outstring, "Border Color Mode = %s\r\n", Vdp2Regs->TVMD & 0x100 ? "Back screen" : "Black");

      AddString(outstring, "Display Resolution = ");
      switch (Vdp2Regs->TVMD & 0x7)
      {
         case 0:
         case 4:
            AddString(outstring, "320");
            break;
         case 1:
         case 5:
            AddString(outstring, "352");
            break;
         case 2:
         case 6:
            AddString(outstring, "640");
            break;
         case 3:
         case 7:
            AddString(outstring, "704");
            break;
         default:
            AddString(outstring, "Invalid");
            break;
      }

      AddString(outstring, " x ");

      switch ((Vdp2Regs->TVMD >> 4) & 0x3)
      {
         case 0:
            AddString(outstring, "224");
            break;
         case 1:
            AddString(outstring, "240");
            break;
         case 2:
            AddString(outstring, "256");
            break;
         default:
            AddString(outstring, "Invalid");
            break;
      }

      if (Vdp2Regs->TVSTAT & 0x1)
      {
         AddString(outstring, "(PAL)\r\n");
      }
      else
      {
         AddString(outstring, "(NTSC)\r\n");
      }

      AddString(outstring, "Interlace Mode = ");
      switch ((Vdp2Regs->TVMD >> 6) & 0x3)
      {
         case 0:
            AddString(outstring, "Non-Interlace\r\n");
            break;
         case 2:
            AddString(outstring, "Single-Density Interlace\r\n");
            break;
         case 3:
            AddString(outstring, "Double-Density Interlace\r\n");
            break;
         default:
            AddString(outstring, "Invalid\r\n");
            break;
      }

      // Latch stuff
      AddString(outstring, "Latches HV counter when %s\r\n", Vdp2Regs->EXTEN & 0x200 ? "external signal triggers it" : "external latch flag is read");
      if (Vdp2Regs->EXTEN & 0x100)
      {
         AddString(outstring, "External Sync is being inputed\r\n");
      }

      // Screen status stuff
      if (Vdp2Regs->TVSTAT & 0x200)
      {
         AddString(outstring, "HV is latched\r\n");
      }

      if (Vdp2Regs->TVSTAT & 0x4)
      {
         AddString(outstring, "During H-Blank\r\n");
      }

      if (Vdp2Regs->TVSTAT & 0x8)
      {
         AddString(outstring, "During V-Blank\r\n");
      }

      if ((Vdp2Regs->TVMD >> 6) & 0x2)
      {
         AddString(outstring, "During %s Field\r\n", Vdp2Regs->TVSTAT & 0x2 ? "Odd" : "Even");
      }

      AddString(outstring, "H Counter = %d\r\n", Vdp2Regs->HCNT);
      AddString(outstring, "V Counter = %d\r\n", Vdp2Regs->VCNT);
      AddString(outstring, "\r\n");

      // Line color screen stuff
      AddString(outstring, "Line Color Screen Stuff\r\n");
      AddString(outstring, "-----------------------\r\n");
      AddString(outstring, "Mode = %s\r\n", Vdp2Regs->LCTA.part.U & 0x8000 ? "Color per line" : "Single color");
      AddString(outstring, "Address = %08lX\r\n", 0x05E00000UL | ((Vdp2Regs->LCTA.all & 0x7FFFFUL) * 2));
      AddString(outstring, "\r\n");

      // Back screen stuff
      AddString(outstring, "Back Screen Stuff\r\n");
      AddString(outstring, "-----------------\r\n");
      AddString(outstring, "Mode = %s\r\n", Vdp2Regs->BKTAU & 0x8000 ? "Color per line" : "Single color");
      AddString(outstring, "Address = %08X\r\n", 0x05E00000 | (((Vdp2Regs->BKTAU & 0x7) << 16)  | Vdp2Regs->BKTAL) * 2);
      outstring = AddColorOffsetInfo(outstring, 0x0020);
      AddString(outstring, "\r\n");

      // Cycle patterns here

      // Sprite stuff
      AddString(outstring, "Sprite Stuff\r\n");
      AddString(outstring, "------------\r\n");
      AddString(outstring, "Sprite Type = %X\r\n", Vdp2Regs->SPCTL & 0xF);
      AddString(outstring, "VDP1 Framebuffer Data Format = %s\r\n", Vdp2Regs->SPCTL & 0x20 ? "RGB and palette" : "Palette only");

      if (Vdp2Regs->SDCTL & 0x100)
      {
         AddString(outstring, "Transparent Shadow Enabled\r\n");
      }

      if (Vdp2Regs->SPCTL & 0x20)
      {
         AddString(outstring, "Sprite Window Enabled\r\n");
      }

      outstring = AddWindowInfoString(outstring, Vdp2Regs->WCTLC >> 8, 1);

      AddString(outstring, "Color RAM Offset = %X\r\n", (Vdp2Regs->CRAOFB >> 4) & 0x7);

      if (Vdp2Regs->CCCTL & 0x40)
      {
         AddString(outstring, "Color Calculation Enabled\r\n");

         if (Vdp2Regs->CCCTL & 0x8000 && (Vdp2Regs->CCCTL & 0x0700) == 0)
         {
            AddString(outstring, "Gradation Calculation Enabled\r\n");
         }
         else if (Vdp2Regs->CCCTL & 0x0400)
         {
            AddString(outstring, "Extended Color Calculation Enabled\r\n");
         }

         AddString(outstring, "Color Calculation Condition = ");

         switch ((Vdp2Regs->SPCTL >> 12) & 0x3)
         {
             case 0:
                AddString(outstring, "Priority <= CC Condition Number");
                break;
             case 1:
                AddString(outstring, "Priority == CC Condition Number");
                break;
             case 2:
                AddString(outstring, "Priority >= CC Condition Number");
                break;
             case 3:
                AddString(outstring, "Color Data MSB");
                break;
             default: break;
         }
         AddString(outstring, "\r\n");

         if (((Vdp2Regs->SPCTL >> 12) & 0x3) != 0x3)
         {
            AddString(outstring, "Color Calculation Condition Number = %d\r\n", (Vdp2Regs->SPCTL >> 8) & 0x7);
         }

         for (i = 0; i < 8; i++)
         {
#ifdef WORDS_BIGENDIAN
            int ratio = sprccrlist[i ^ 1] & 0x7;
#else
            int ratio = sprccrlist[i] & 0x7;
#endif
            AddString(outstring, "Color Calculation Ratio %d = %d:%d\r\n", i, 31 - ratio, 1 + ratio);
         }
      }

      for (i = 0; i < 8; i++)
      {
#ifdef WORDS_BIGENDIAN
         int priority = sprprilist[i ^ 1] & 0x7;
#else
         int priority = sprprilist[i] & 0x7;
#endif
         AddString(outstring, "Priority %d = %d\r\n", i, priority);
      }

      outstring = AddColorOffsetInfo(outstring, 0x0040);
      *isenabled = 1;
   }
   else
   {
      *isenabled = 0;
   }
}
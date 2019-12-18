#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int CMDCTRL; int CMDSIZE; int CMDPMOD; int CMDCOLR; scalar_t__ CMDGRDA; scalar_t__ CMDSRCA; int /*<<< orphan*/  CMDYA; int /*<<< orphan*/  CMDXA; int /*<<< orphan*/  CMDYC; int /*<<< orphan*/  CMDXC; int /*<<< orphan*/  CMDYD; int /*<<< orphan*/  CMDXD; int /*<<< orphan*/  CMDYB; int /*<<< orphan*/  CMDXB; } ;
typedef  TYPE_1__ vdp1cmd_struct ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  AddString (char*,char*,...) ; 
 int T1ReadWord (int /*<<< orphan*/ ,int) ; 
 int Vdp1DebugGetCommandNumberAddr (int) ; 
 int /*<<< orphan*/  Vdp1Ram ; 
 int /*<<< orphan*/  Vdp1ReadCommand (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void Vdp1DebugCommand(u32 number, char *outstring)
{
   u16 command;
   vdp1cmd_struct cmd;
   u32 addr;

   if ((addr = Vdp1DebugGetCommandNumberAddr(number)) == 0xFFFFFFFF)
      return;

   command = T1ReadWord(Vdp1Ram, addr);

   if (command & 0x8000)
   {
      // Draw End
      outstring[0] = 0x00;
      return;
   }

   if (command & 0x4000)
   {
      AddString(outstring, "Command is skipped\r\n");
      return;
   }

   Vdp1ReadCommand(&cmd, addr, Vdp1Ram);

   switch (cmd.CMDCTRL & 0x000F)
   {
      case 0:
         AddString(outstring, "Normal Sprite\r\n");
         AddString(outstring, "x = %d, y = %d\r\n", cmd.CMDXA, cmd.CMDYA);
         break;
      case 1:
         AddString(outstring, "Scaled Sprite\r\n");

         AddString(outstring, "Zoom Point: ");

         switch ((cmd.CMDCTRL >> 8) & 0xF)
         {
            case 0x0:
               AddString(outstring, "Only two coordinates\r\n");
               break;
            case 0x5:
               AddString(outstring, "Upper-left\r\n");
               break;
            case 0x6:
               AddString(outstring, "Upper-center\r\n");
               break;
            case 0x7:
               AddString(outstring, "Upper-right\r\n");
               break;
            case 0x9:
               AddString(outstring, "Center-left\r\n");
               break;
            case 0xA:
               AddString(outstring, "Center-center\r\n");
               break;
            case 0xB:
               AddString(outstring, "Center-right\r\n");
               break;
            case 0xC:
               AddString(outstring, "Lower-left\r\n");
               break;
            case 0xE:
               AddString(outstring, "Lower-center\r\n");
               break;
            case 0xF:
               AddString(outstring, "Lower-right\r\n");
               break;
            default: break;
         }

         if (((cmd.CMDCTRL >> 8) & 0xF) == 0)
         {
            AddString(outstring, "xa = %d, ya = %d, xc = %d, yc = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXC, cmd.CMDYC);
         }
         else
         {
            AddString(outstring, "xa = %d, ya = %d, xb = %d, yb = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXB, cmd.CMDYB);
         }

         break;
      case 2:
         AddString(outstring, "Distorted Sprite\r\n");
         AddString(outstring, "x1 = %d, y1 = %d, x2 = %d, y2 = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXB, cmd.CMDYB);
         AddString(outstring, "x3 = %d, y3 = %d, x4 = %d, y4 = %d\r\n", cmd.CMDXC, cmd.CMDYC, cmd.CMDXD, cmd.CMDYD);
         break;
      case 3:
         AddString(outstring, "Distorted Sprite *\r\n");
         AddString(outstring, "x1 = %d, y1 = %d, x2 = %d, y2 = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXB, cmd.CMDYB);
         AddString(outstring, "x3 = %d, y3 = %d, x4 = %d, y4 = %d\r\n", cmd.CMDXC, cmd.CMDYC, cmd.CMDXD, cmd.CMDYD);
         break;
      case 4:
         AddString(outstring, "Polygon\r\n");
         AddString(outstring, "x1 = %d, y1 = %d, x2 = %d, y2 = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXB, cmd.CMDYB);
         AddString(outstring, "x3 = %d, y3 = %d, x4 = %d, y4 = %d\r\n", cmd.CMDXC, cmd.CMDYC, cmd.CMDXD, cmd.CMDYD);
         break;
      case 5:
         AddString(outstring, "Polyline\r\n");
         AddString(outstring, "x1 = %d, y1 = %d, x2 = %d, y2 = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXB, cmd.CMDYB);
         AddString(outstring, "x3 = %d, y3 = %d, x4 = %d, y4 = %d\r\n", cmd.CMDXC, cmd.CMDYC, cmd.CMDXD, cmd.CMDYD);
         break;
      case 6:
         AddString(outstring, "Line\r\n");
         AddString(outstring, "x1 = %d, y1 = %d, x2 = %d, y2 = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXB, cmd.CMDYB);
         break;
      case 7:
         AddString(outstring, "Polyline *\r\n");
         AddString(outstring, "x1 = %d, y1 = %d, x2 = %d, y2 = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXB, cmd.CMDYB);
         AddString(outstring, "x3 = %d, y3 = %d, x4 = %d, y4 = %d\r\n", cmd.CMDXC, cmd.CMDYC, cmd.CMDXD, cmd.CMDYD);
         break;
      case 8:
         AddString(outstring, "User Clipping\r\n");
         AddString(outstring, "x1 = %d, y1 = %d, x2 = %d, y2 = %d\r\n", cmd.CMDXA, cmd.CMDYA, cmd.CMDXC, cmd.CMDYC);
         break;
      case 9:
         AddString(outstring, "System Clipping\r\n");
         AddString(outstring, "x1 = 0, y1 = 0, x2 = %d, y2 = %d\r\n", cmd.CMDXC, cmd.CMDYC);
         break;
      case 10:
         AddString(outstring, "Local Coordinates\r\n");
         AddString(outstring, "x = %d, y = %d\r\n", cmd.CMDXA, cmd.CMDYA);
         break;
      default:
         AddString(outstring, "Invalid command\r\n");
         return;
   }

   // Only Sprite commands use CMDSRCA, CMDSIZE
   if (!(cmd.CMDCTRL & 0x000C))
   {
      AddString(outstring, "Texture address = %08X\r\n", ((unsigned int)cmd.CMDSRCA) << 3);
      AddString(outstring, "Texture width = %d, height = %d\r\n", (cmd.CMDSIZE & 0x3F00) >> 5, cmd.CMDSIZE & 0xFF);
      AddString(outstring, "Texture read direction: ");

      switch ((cmd.CMDCTRL >> 4) & 0x3)
      {
         case 0:
            AddString(outstring, "Normal\r\n");
            break;
         case 1:
            AddString(outstring, "Reversed horizontal\r\n");
            break;
         case 2:
            AddString(outstring, "Reversed vertical\r\n");
            break;
         case 3:
            AddString(outstring, "Reversed horizontal and vertical\r\n");
            break;
         default: break;
      }
   }

   // Only draw commands use CMDPMOD
   if (!(cmd.CMDCTRL & 0x0008))
   {
      if (cmd.CMDPMOD & 0x8000)
      {
         AddString(outstring, "MSB set\r\n");
      }

      if (cmd.CMDPMOD & 0x1000)
      {
         AddString(outstring, "High Speed Shrink Enabled\r\n");
      }

      if (!(cmd.CMDPMOD & 0x0800))
      {
         AddString(outstring, "Pre-clipping Enabled\r\n");
      }

      if (cmd.CMDPMOD & 0x0400)
      {
         AddString(outstring, "User Clipping Enabled\r\n");
         AddString(outstring, "Clipping Mode = %d\r\n", (cmd.CMDPMOD >> 9) & 0x1);
      }

      if (cmd.CMDPMOD & 0x0100)
      {
         AddString(outstring, "Mesh Enabled\r\n");
      }

      if (!(cmd.CMDPMOD & 0x0080))
      {
         AddString(outstring, "End Code Enabled\r\n");
      }

      if (!(cmd.CMDPMOD & 0x0040))
      {
         AddString(outstring, "Transparent Pixel Enabled\r\n");
      }

      AddString(outstring, "Color mode: ");

      switch ((cmd.CMDPMOD >> 3) & 0x7)
      {
         case 0:
            AddString(outstring, "4 BPP(16 color bank)\r\n");
            AddString(outstring, "Color bank: %08X\r\n", (cmd.CMDCOLR << 3));
            break;
         case 1:
            AddString(outstring, "4 BPP(16 color LUT)\r\n");
            AddString(outstring, "Color lookup table: %08X\r\n", (cmd.CMDCOLR << 3));
            break;
         case 2:
            AddString(outstring, "8 BPP(64 color bank)\r\n");
            AddString(outstring, "Color bank: %08X\r\n", (cmd.CMDCOLR << 3));
            break;
         case 3:
            AddString(outstring, "8 BPP(128 color bank)\r\n");
            AddString(outstring, "Color bank: %08X\r\n", (cmd.CMDCOLR << 3));
            break;
         case 4:
            AddString(outstring, "8 BPP(256 color bank)\r\n");
            AddString(outstring, "Color bank: %08X\r\n", (cmd.CMDCOLR << 3));
            break;
         case 5:
            AddString(outstring, "15 BPP(RGB)\r\n");

            // Only non-textured commands
            if (cmd.CMDCTRL & 0x0004)
            {
               AddString(outstring, "Non-textured color: %04X\r\n", cmd.CMDCOLR);
            }
            break;
         default: break;
      }

      AddString(outstring, "Color Calc. mode: ");

      switch (cmd.CMDPMOD & 0x7)
      {
         case 0:
            AddString(outstring, "Replace\r\n");
            break;
         case 1:
            AddString(outstring, "Cannot overwrite/Shadow\r\n");
            break;
         case 2:
            AddString(outstring, "Half-luminance\r\n");
            break;
         case 3:
            AddString(outstring, "Replace/Half-transparent\r\n");
            break;
         case 4:
            AddString(outstring, "Gouraud Shading\r\n");
            AddString(outstring, "Gouraud Shading Table = %08X\r\n", ((unsigned int)cmd.CMDGRDA) << 3);
            break;
         case 6:
            AddString(outstring, "Gouraud Shading + Half-luminance\r\n");
            AddString(outstring, "Gouraud Shading Table = %08X\r\n", ((unsigned int)cmd.CMDGRDA) << 3);
            break;
         case 7:
            AddString(outstring, "Gouraud Shading/Gouraud Shading + Half-transparent\r\n");
            AddString(outstring, "Gouraud Shading Table = %08X\r\n", ((unsigned int)cmd.CMDGRDA) << 3);
            break;
         default: break;
      }
   }
}
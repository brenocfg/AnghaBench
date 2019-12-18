#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
 int c68k_word_read (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,unsigned int,...) ; 

__attribute__((used)) static int seteafieldstr(u32 addr, u16 modereg, int *addsize, char *outstring)
{
   switch ((modereg >> 3) & 0x7)
   {
      case 0x0:
         // Dn         
         return sprintf(outstring, "d%d", modereg & 0x7);
      case 0x1:
         // An         
         return sprintf(outstring, "a%d", modereg & 0x7);
      case 0x2:
         // (An)         
         return sprintf(outstring, "(a%d)", modereg & 0x7);
      case 0x3:
         // (An)+         
         return sprintf(outstring, "(a%d)+", modereg & 0x7);
      case 0x4:
         // -(An)         
         return sprintf(outstring, "-(a%d)", modereg & 0x7);
      case 0x5:
         // (d16, An)
         *addsize += 2;         
         return sprintf(outstring, "0x%X(a%d)", (unsigned int)c68k_word_read(addr), modereg & 0x7);
      case 0x6:
         // (d8,An,Xn)
         // fix me
         *addsize += 2;         
         return sprintf(outstring, "0x%X(a%d, Xn)", (unsigned int)(c68k_word_read(addr) & 0xFF), modereg & 0x7);
      case 0x7:
         switch (modereg & 0x7)
         {
            case 0x0:
               // (xxx).W
               *addsize += 2; // fix me?
               return sprintf(outstring, "(0x%X).w", (unsigned int)c68k_word_read(addr));
            case 0x1:
               // (xxx).L
               *addsize += 4; // fix me?
               return sprintf(outstring, "(0x%X).l", (unsigned int)((c68k_word_read(addr) << 16) | c68k_word_read(addr+2)));
            case 0x4:
               // #<data>
               *addsize += 2; // fix me?
               return sprintf(outstring, "#0x%X", (unsigned int)c68k_word_read(addr));
            case 0x2:
               // (d16,PC)
               *addsize += 2;               
               return sprintf(outstring, "0x%X(PC)", (unsigned int)c68k_word_read(addr));
            case 0x3:
               // (d8,PC,Xn)
               // fix me
               return 0;
            default: break;
         }
      default: break;
   }

   return 0;
}
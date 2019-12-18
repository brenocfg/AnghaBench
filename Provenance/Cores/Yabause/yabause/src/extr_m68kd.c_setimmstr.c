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
 int sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static int setimmstr(u32 addr, u16 size, int *addsize, char *outstring)
{
   switch (size & 0x3)
   {
      case 0x0:
         *addsize+=2;
         return sprintf(outstring, "#0x%X", (unsigned int)(c68k_word_read(addr) & 0xFF));
      case 0x1:
         *addsize+=2;
         return sprintf(outstring, "#0x%X", (unsigned int)c68k_word_read(addr));
      case 0x2:
         *addsize+=4;
         return sprintf(outstring, "#0x%X", (unsigned int)((c68k_word_read(addr) << 16) | c68k_word_read(addr+2)));
      default:
         return 0;
   }
}
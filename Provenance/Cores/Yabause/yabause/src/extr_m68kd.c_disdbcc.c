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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
typedef  scalar_t__ s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 scalar_t__ c68k_word_read (scalar_t__) ; 
 int /*<<< orphan*/  setcondstr (int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int disdbcc(u32 addr, u16 op, char *outstring)
{
   outstring += sprintf(outstring, "db");
   outstring += setcondstr(op >> 8, outstring);
   outstring += sprintf(outstring, "   ");
   sprintf(outstring, " d%d, %X", op & 0x7, (unsigned int)((s32)addr+2+(s32)(s16)c68k_word_read(addr+2)));
   return 4;
}
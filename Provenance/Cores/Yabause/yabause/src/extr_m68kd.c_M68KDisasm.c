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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_2__ {int mask; int inst; scalar_t__ (* disasm ) (scalar_t__,int,char*) ;int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  c68k_word_read (scalar_t__) ; 
 TYPE_1__* instruction ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 scalar_t__ stub1 (scalar_t__,int,char*) ; 

u32 M68KDisasm(u32 addr, char *outstring)
{
   int i;

   outstring += sprintf(outstring, "%05X: ", (unsigned int)addr);

   for (i = 0; instruction[i].name != NULL; i++)
   {
      u16 op = (u16)c68k_word_read(addr);

      if ((op & instruction[i].mask) == instruction[i].inst)
      {
         addr += instruction[i].disasm(addr, op, outstring);
         return addr;
      }
   }

   sprintf(outstring, "unknown");
   return (addr+2);
}
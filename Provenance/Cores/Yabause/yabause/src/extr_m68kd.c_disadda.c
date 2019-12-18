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

/* Variables and functions */
 int /*<<< orphan*/  seteafieldstr (scalar_t__,int,int*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int disadda(u32 addr, u16 op, char *outstring)
{
   int size=2;

   outstring += sprintf(outstring, "adda");
   if ((op & 0x1C0) == 0xC0)
      outstring += sprintf(outstring, ".w  ");
   else
      outstring += sprintf(outstring, ".l  ");
   outstring += seteafieldstr(addr+size, op, &size, outstring);
   outstring += sprintf(outstring, ", a%d", (op >> 9) & 0x7);
   return size;
}
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

/* Variables and functions */

int strip_opname(const char *str,char *name)

// Strip out the opcode name and return in *name

{
   int pos;

   pos = 0;

   while((str[pos] != 32) && (str[pos] != 0))
   {
      name[pos] = str[pos];
      pos++;
   }

   name[pos] = 0;

   return pos;
}
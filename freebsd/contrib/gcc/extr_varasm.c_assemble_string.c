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
 int /*<<< orphan*/  ASM_OUTPUT_ASCII (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  asm_out_file ; 

void
assemble_string (const char *p, int size)
{
  int pos = 0;
  int maximum = 2000;

  /* If the string is very long, split it up.  */

  while (pos < size)
    {
      int thissize = size - pos;
      if (thissize > maximum)
	thissize = maximum;

      ASM_OUTPUT_ASCII (asm_out_file, p, thissize);

      pos += thissize;
      p += thissize;
    }
}
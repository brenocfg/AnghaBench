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
 int /*<<< orphan*/  ASM_OUTPUT_ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BITS_PER_UNIT ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  floor_log2 (int) ; 

void
assemble_align (int align)
{
  if (align > BITS_PER_UNIT)
    {
      ASM_OUTPUT_ALIGN (asm_out_file, floor_log2 (align / BITS_PER_UNIT));
    }
}
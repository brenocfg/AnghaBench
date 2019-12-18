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
 int /*<<< orphan*/  ASM_OUTPUT_LABEL (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  asm_out_file ; 

void
assemble_label (const char *name)
{
  ASM_OUTPUT_LABEL (asm_out_file, name);
}
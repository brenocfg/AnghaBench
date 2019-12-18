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
 int /*<<< orphan*/  assem_debug (char*,int,int) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_rex (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_w32 (int) ; 

void emit_writedword_imm32(int imm, int addr)
{
  assem_debug("movq $%x,%x\n",imm,addr);
  output_rex(1,0,0,0);
  output_byte(0xC7);
  output_modrm(0,5,0);
  output_w32(addr-(int)out-8); // Note: rip-relative in 64-bit mode
  output_w32(imm); // Note: This 32-bit value will be sign extended
}
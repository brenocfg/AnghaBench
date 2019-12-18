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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_sib (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 

void emit_writeword_imm_esp(int imm, int addr)
{
  assem_debug("mov $%x,%x(%%esp)\n",imm,addr);
  assert(addr>=-128&&addr<128);
  output_byte(0xC7);
  output_modrm(1,4,0);
  output_sib(0,4,4);
  output_byte(addr);
  output_w32(imm);
}
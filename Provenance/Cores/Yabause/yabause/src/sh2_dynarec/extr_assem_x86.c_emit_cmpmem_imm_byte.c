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
typedef  int /*<<< orphan*/  pointer ;

/* Variables and functions */
 int /*<<< orphan*/  assem_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_w32 (int /*<<< orphan*/ ) ; 

void emit_cmpmem_imm_byte(pointer addr,int imm)
{
  assert(imm<128&&imm>=-127);
  assem_debug("cmpb $%d,%x\n",imm,addr);
  output_byte(0x80);
  output_modrm(0,5,7);
  output_w32(addr);
  output_byte(imm);
}
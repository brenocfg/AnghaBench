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
 int /*<<< orphan*/  assem_debug (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_shrimm (int,int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_cmpmem_indexedsr12_imm(int addr,int r,int imm)
{
  assert(imm<128&&imm>=-127);
  assert(r>=0&&r<8);
  emit_shrimm(r,12,r);
  assem_debug("cmp $%d,%x+%%%s\n",imm,addr,regname[r]);
  output_byte(0x80);
  output_modrm(2,r,7);
  output_w32(addr);
  output_byte(imm);
}
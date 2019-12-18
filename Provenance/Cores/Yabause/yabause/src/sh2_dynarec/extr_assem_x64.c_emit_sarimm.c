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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  output_byte (unsigned int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_sarimm(int rs,unsigned int imm,int rt)
{
  if(rs==rt) {
    assem_debug("sar %%%s,%d\n",regname[rt],imm);
    assert(imm>0);
    if(imm==1) output_byte(0xD1);
    else output_byte(0xC1);
    output_modrm(3,rt,7);
    if(imm>1) output_byte(imm);
  }
  else {
    emit_mov(rs,rt);
    emit_sarimm(rt,imm,rt);
  }
}
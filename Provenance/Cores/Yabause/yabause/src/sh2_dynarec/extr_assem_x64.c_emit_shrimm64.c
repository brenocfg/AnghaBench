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
 int /*<<< orphan*/  emit_shrimm (int,unsigned int,int) ; 
 int /*<<< orphan*/  output_byte (unsigned int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_rex (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_shrimm64(int rs,unsigned int imm,int rt)
{
  assert(rs==rt);
  if(rs==rt) {
    assem_debug("shr %%%s,%d\n",regname[rt],imm);
    assert(imm>0);
    output_rex(1,0,0,rt>>3);
    if(imm==1) output_byte(0xD1);
    else output_byte(0xC1);
    output_modrm(3,rt,5);
    if(imm>1) output_byte(imm);
  }
  else {
    emit_mov(rs,rt);
    emit_shrimm(rt,imm,rt);
  }
}
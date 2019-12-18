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
struct regstat {int dummy; } ;

/* Variables and functions */
 scalar_t__ SR ; 
 scalar_t__ TBIT ; 
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,scalar_t__) ; 
 int /*<<< orphan*/  alloc_reg_temp (struct regstat*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_const (struct regstat*,scalar_t__) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,scalar_t__) ; 
 int get_const (struct regstat*,scalar_t__) ; 
 int* imm ; 
 scalar_t__ is_const (struct regstat*,scalar_t__) ; 
 int* minimum_free_regs ; 
 int* opcode ; 
 int* opcode2 ; 
 scalar_t__* rs1 ; 
 scalar_t__* rt1 ; 
 int /*<<< orphan*/  set_const (struct regstat*,scalar_t__,int) ; 

void imm8_alloc(struct regstat *current,int i)
{
  //if(rs1[i]>=0&&needed_again(rs1[i],i)) alloc_reg(current,i,rs1[i]);
  //else lt1[i]=rs1[i];
  alloc_reg(current,i,rs1[i]);
  if(rt1[i]>=0&&rt1[i]!=TBIT) alloc_reg(current,i,rt1[i]);
  if(opcode[i]==0x7) { // ADD
    if(is_const(current,rs1[i])) {
      int v=get_const(current,rs1[i]);
      set_const(current,rt1[i],v+imm[i]);
    }
    else clear_const(current,rt1[i]);
  }
  else if(opcode[i]==0x8) { // CMP/EQ
    alloc_reg(current,i,SR); // Liveness analysis on TBIT?
    dirty_reg(current,SR);
    alloc_reg_temp(current,i,-1);
    minimum_free_regs[i]=1;
  }
  else if(opcode[i]==12) {
    if(opcode2[i]==8) { // TST
      alloc_reg(current,i,SR); // Liveness analysis on TBIT?
      dirty_reg(current,SR);
      alloc_reg_temp(current,i,-1);
      minimum_free_regs[i]=1;
    }else
    // AND/XOR/OR
    if(is_const(current,rs1[i])) {
      int v=get_const(current,rs1[i]);
      if(opcode2[i]==0x09) set_const(current,rt1[i],v&imm[i]);
      if(opcode2[i]==0x0a) set_const(current,rt1[i],v^imm[i]);
      if(opcode2[i]==0x0b) set_const(current,rt1[i],v|imm[i]);
    }
    else clear_const(current,rt1[i]);
  }
  else { // opcode[i]==0xE
    assert(opcode[i]==0xE);
    set_const(current,rt1[i],imm[i]); // MOV
  }
  if(rt1[i]>=0&&rt1[i]!=TBIT) dirty_reg(current,rt1[i]);
}
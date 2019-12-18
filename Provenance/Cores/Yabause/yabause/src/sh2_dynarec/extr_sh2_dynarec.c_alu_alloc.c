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
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_reg_temp (struct regstat*,int,int) ; 
 int /*<<< orphan*/  clear_const (struct regstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,int /*<<< orphan*/ ) ; 
 int* minimum_free_regs ; 
 scalar_t__ needed_again (int /*<<< orphan*/ ,int) ; 
 int* opcode ; 
 int* opcode2 ; 
 int /*<<< orphan*/ * rs1 ; 
 int /*<<< orphan*/ * rs2 ; 
 int /*<<< orphan*/ * rt1 ; 

void alu_alloc(struct regstat *current,int i)
{
  if(opcode[i]==2) {
    alloc_reg(current,i,rs1[i]);
    alloc_reg(current,i,rs2[i]);
    clear_const(current,rs2[i]);
    if(opcode2[i]>8&&opcode2[i]<=11) { // AND/XOR/OR
      alloc_reg(current,i,rt1[i]);
    }
    else  // TST or CMP/STR
    {
      alloc_reg(current,i,SR); // Liveness analysis on TBIT?
      dirty_reg(current,SR);
      //#ifdef __x86__ ?
      //#ifdef NEEDS_TEMP
      if(opcode2[i]==8) { // TST
        alloc_reg_temp(current,i,-1);
        minimum_free_regs[i]=1;
      }
      if(opcode2[i]==12) { // CMP/STR
        alloc_reg_temp(current,i,-1);
        minimum_free_regs[i]=1;
      }
    }
  }
  if(opcode[i]==3) {
    alloc_reg(current,i,rs1[i]);
    alloc_reg(current,i,rs2[i]);
    clear_const(current,rs2[i]);
    if(opcode2[i]<8) { // CMP intructions
      alloc_reg(current,i,SR); // Liveness analysis on TBIT?
      dirty_reg(current,SR);
      alloc_reg_temp(current,i,-1);
      minimum_free_regs[i]=1;
    }else{ // ADD/SUB
      alloc_reg(current,i,rt1[i]);
      if(opcode2[i]&3) {
        alloc_reg(current,i,SR);
        dirty_reg(current,SR);
        //#ifdef NEEDS_TEMP
        if((opcode2[i]&3)==3) {
          // Need a temporary register for ADDV/SUBV on x86
          alloc_reg_temp(current,i,-1);
          minimum_free_regs[i]=1;
        }
      }
    }
  }
  if(opcode[i]==4) { // DT/CMPPZ/CMPPL
    // Single operand forms
    alloc_reg(current,i,rs1[i]);
    if(opcode2[i]==0) dirty_reg(current,rt1[i]); // DT
    alloc_reg(current,i,SR); // Liveness analysis on TBIT?
    dirty_reg(current,SR);
    if(opcode2[i]>0) {
      alloc_reg_temp(current,i,-1);
      minimum_free_regs[i]=1;
    }
  }
  if(opcode[i]==6) { // NOT/NEG/NEGC
    if(needed_again(rs1[i],i)) alloc_reg(current,i,rs1[i]);
    alloc_reg(current,i,rt1[i]);
    if(opcode2[i]==8||opcode2[i]==9) { // SWAP needs temp (?)
      alloc_reg_temp(current,i,-1);
      minimum_free_regs[i]=1;
    }
    if(opcode2[i]==10) {
      // NEGC sets T bit
      alloc_reg(current,i,SR); // Liveness analysis on TBIT?
      dirty_reg(current,SR);
    }
  }
  clear_const(current,rs1[i]);
  clear_const(current,rt1[i]);
  dirty_reg(current,rt1[i]);
}
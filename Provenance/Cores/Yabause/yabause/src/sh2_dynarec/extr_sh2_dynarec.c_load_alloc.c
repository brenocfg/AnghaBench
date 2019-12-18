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
struct regstat {scalar_t__* regmap; } ;

/* Variables and functions */
 scalar_t__ DUALIND ; 
 scalar_t__ GBRIND ; 
 scalar_t__ MOREG ; 
 scalar_t__ POSTINC ; 
 scalar_t__ SR ; 
 scalar_t__ TBIT ; 
 scalar_t__* addrmode ; 
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,scalar_t__) ; 
 int /*<<< orphan*/  alloc_reg_temp (struct regstat*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_const (struct regstat*,scalar_t__) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,scalar_t__) ; 
 int get_const (struct regstat*,scalar_t__) ; 
 scalar_t__ get_reg (scalar_t__*,scalar_t__) ; 
 scalar_t__ is_const (struct regstat*,scalar_t__) ; 
 int* minimum_free_regs ; 
 scalar_t__ needed_again (scalar_t__,int) ; 
 int* opcode ; 
 int* opcode2 ; 
 scalar_t__* rs1 ; 
 scalar_t__* rs2 ; 
 scalar_t__* rt1 ; 
 scalar_t__* rt2 ; 
 int /*<<< orphan*/  set_const (struct regstat*,scalar_t__,int) ; 

void load_alloc(struct regstat *current,int i)
{
  int hr;
  clear_const(current,rt1[i]);
  //if(rs1[i]!=rt1[i]&&needed_again(rs1[i],i)) clear_const(current,rs1[i]); // Does this help or hurt?
  if(needed_again(rs1[i],i)) alloc_reg(current,i,rs1[i]);
 // if(rs2[i]>=0) alloc_reg(current,i,rs2[i]);
  alloc_reg(current,i,rt1[i]==TBIT?SR:rt1[i]);
  if(addrmode[i]==DUALIND||addrmode[i]==GBRIND) {
    alloc_reg(current,i,rs1[i]);
    alloc_reg(current,i,rs2[i]);
    if(!is_const(current,rs1[i])||!is_const(current,rs2[i])) {
      // Both must be constants to propagate the sum
      clear_const(current,rs1[i]);
      clear_const(current,rs2[i]);
    }
  }
  else
  if(addrmode[i]==POSTINC) {
    if(is_const(current,rt2[i])) {
      int v=get_const(current,rt2[i]);
      set_const(current,rt2[i],v+(1<<((opcode[i]==4)?2:(opcode2[i]&3))));
      // Note: constant is preincremented, address_generation corrects the offset
    }
    else {
      alloc_reg(current,i,rt2[i]);
      dirty_reg(current,rt2[i]);
    }
  }

  // Need a register to load from memory_map
  alloc_reg(current,i,MOREG);
  if(rt1[i]==TBIT||get_reg(current->regmap,rt1[i])<0) {
    // dummy load, but we still need a register to calculate the address
    alloc_reg_temp(current,i,-1);
    minimum_free_regs[i]=1;
  }
  if(rt1[i]==TBIT) dirty_reg(current,SR);
  else dirty_reg(current,rt1[i]);
  
  // Make MOREG a temporary, give pass 5 another register to work with
  hr=get_reg(current->regmap,MOREG);
  assert(hr>=0);
  assert(current->regmap[hr]==MOREG);
  current->regmap[hr]=-1;
  minimum_free_regs[i]++;
}
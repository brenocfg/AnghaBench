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
struct regstat {int* regmap; } ;

/* Variables and functions */
 scalar_t__ DUALIND ; 
 int MOREG ; 
 scalar_t__ PREDEC ; 
 scalar_t__* addrmode ; 
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,int) ; 
 int /*<<< orphan*/  alloc_reg_temp (struct regstat*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_const (struct regstat*,int) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,int) ; 
 int get_const (struct regstat*,int) ; 
 int get_reg (int*,int) ; 
 scalar_t__ is_const (struct regstat*,int) ; 
 int* minimum_free_regs ; 
 scalar_t__ needed_again (int,int) ; 
 int* opcode ; 
 int* opcode2 ; 
 int* rs1 ; 
 int* rs2 ; 
 int* rs3 ; 
 int* rt1 ; 
 int /*<<< orphan*/  set_const (struct regstat*,int,int) ; 

void store_alloc(struct regstat *current,int i)
{
  int hr;
  //printf("%x: eax=%d ecx=%d edx=%d ebx=%d ebp=%d esi=%d edi=%d\n",start+i*2,current->regmap[0],current->regmap[1],current->regmap[2],current->regmap[3],current->regmap[5],current->regmap[6],current->regmap[7]);
  if(addrmode[i]==DUALIND) {
    alloc_reg(current,i,rs2[i]);
    alloc_reg(current,i,0); // rs3[i]
    if(!is_const(current,rs2[i])||!is_const(current,rs3[i])) {
      // Both must be constants to propagate the sum
      clear_const(current,rs2[i]);
      clear_const(current,rs3[i]);
    }
  }
  if(addrmode[i]==PREDEC) {
    if(is_const(current,rt1[i])) {
      int v=get_const(current,rt1[i]);
      set_const(current,rt1[i],v-(1<<((opcode[i]==4)?2:(opcode2[i]&3))));
    }
    else {
      alloc_reg(current,i,rt1[i]);
      dirty_reg(current,rt1[i]);
    }
  }
  if(needed_again(rs2[i],i)) alloc_reg(current,i,rs2[i]);
  clear_const(current,rs1[i]);
  alloc_reg(current,i,rs1[i]);
  // Need a register to load from memory_map
  alloc_reg(current,i,MOREG);
  
  // We need a temporary register for address generation
  alloc_reg_temp(current,i,-1);
  minimum_free_regs[i]=1;

  // Make MOREG a temporary, give pass 5 another register to work with
  hr=get_reg(current->regmap,MOREG);
  assert(hr>=0);
  assert(current->regmap[hr]==MOREG);
  current->regmap[hr]=-1;
  minimum_free_regs[i]++;
}
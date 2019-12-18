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
typedef  int u32 ;
struct regstat {scalar_t__* regmap; int /*<<< orphan*/  dirty; } ;
typedef  int pointer ;

/* Variables and functions */
 scalar_t__ CCREG ; 
 int /*<<< orphan*/  CC_STUB ; 
 int CLOCK_DIVIDER ; 
 char HOST_CCREG ; 
 unsigned int HOST_REGS ; 
 int /*<<< orphan*/  LOADL_STUB ; 
 int MMREG ; 
 int MOREG ; 
 int SR ; 
 int /*<<< orphan*/  STOREL_STUB ; 
 int TAKEN ; 
 int VBR ; 
 int /*<<< orphan*/  add_stub (int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* ccadj ; 
 int* cycles ; 
 int do_map_r (int,int,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_map_r_branch (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int do_map_w (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_map_w_branch (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_addimm_and_set_flags (int,char) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_jns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_loadreg (scalar_t__,char) ; 
 int /*<<< orphan*/  emit_movimm (int,int) ; 
 int /*<<< orphan*/  emit_readword_indexed_map (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  emit_rorimm (int,int,int) ; 
 int /*<<< orphan*/  emit_writeword_indexed_map (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  emit_zeroreg (char) ; 
 void* get_reg (scalar_t__*,int) ; 
 int* imm ; 
 int /*<<< orphan*/  is_delayslot ; 
 int** jump_vaddr_reg ; 
 int* opcode ; 
 int* opcode2 ; 
 int* opcode3 ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  set_jump_target (int,int) ; 
 size_t slave ; 
 int start ; 
 int /*<<< orphan*/  store_regs_bt (scalar_t__*,int /*<<< orphan*/ ,int) ; 

void system_assemble(int i,struct regstat *i_regs)
{
  signed char ccreg=get_reg(i_regs->regmap,CCREG);
  assert(ccreg==HOST_CCREG);
  assert(!is_delayslot);
  if(opcode[i]==0&&opcode2[i]==11&&opcode3[i]==1) { // SLEEP
    pointer jaddr, return_address;
    emit_addimm(HOST_CCREG,CLOCK_DIVIDER*ccadj[i],HOST_CCREG);
    jaddr=(pointer)out;
    emit_jns(0);
    return_address=(pointer)out;
    emit_zeroreg(HOST_CCREG);
    set_jump_target(jaddr,(pointer)out);
    add_stub(CC_STUB,(int)out,return_address,0,i,start+i*2,TAKEN,0);
    emit_jmp(0);
    // DEBUG: Count in multiples of three to match interpreter
    //emit_addimm_and_set_flags(CLOCK_DIVIDER*3,HOST_CCREG);
    //add_stub(CC_STUB,(int)out,return_address,0,i,start+i*2,TAKEN,0);
    //emit_jns(0);
    emit_jmp(return_address);
  }
  else {
    int b,t,sr,st,map=-1,cache=-1;
    int jaddr=0;
    unsigned int hr;
    u32 reglist=0;
    assert(opcode[i]==12); // TRAPA
    t=get_reg(i_regs->regmap,-1);
    b=get_reg(i_regs->regmap,VBR);
    sr=get_reg(i_regs->regmap,SR);
    st=get_reg(i_regs->regmap,15); // STACK
    for(hr=0;hr<HOST_REGS;hr++) {
      if(i_regs->regmap[hr]>=0) reglist|=1<<hr;
    }
    assert(t>=0);
    assert(b>=0);
    assert(sr>=0);
    assert(st>=0);
    emit_addimm(st,-4,st);
    map=get_reg(i_regs->regmap,MOREG);
    cache=get_reg(i_regs->regmap,MMREG);
    assert(map>=0);
    reglist&=~(1<<map);
    map=do_map_w(st,st,map,cache,0,0,0);
    do_map_w_branch(map,0,0,&jaddr);
    // Save SR
    emit_rorimm(sr,16,sr);
    emit_writeword_indexed_map(sr,0,st,map,map);
    emit_rorimm(sr,16,sr);
    if(jaddr) {
      add_stub(STOREL_STUB,jaddr,(int)out,i,st,(int)i_regs,ccadj[i],reglist);
    }
    emit_addimm(st,-4,st);
    store_regs_bt(i_regs->regmap,i_regs->dirty,-1);
    emit_movimm(start+i*2+2,sr);
    emit_addimm(b,imm[i]<<2,b);
    map=do_map_w(st,st,map,cache,0,0,0);
    do_map_w_branch(map,0,0,&jaddr);
    // Save PC
    emit_rorimm(sr,16,sr);
    emit_writeword_indexed_map(sr,0,st,map,map);
    if(jaddr) {
      add_stub(STOREL_STUB,jaddr,(int)out,i,st,(int)i_regs,ccadj[i],reglist);
    }
    // Load PC
    map=do_map_r(b,b,map,cache,0,-1,-1,0,0);
    do_map_r_branch(map,0,0,&jaddr);
    emit_readword_indexed_map(0,b,map,t);
    emit_rorimm(t,16,t);
    if(jaddr)
      add_stub(LOADL_STUB,jaddr,(int)out,i,t,(int)i_regs,ccadj[i],reglist);
    if(i_regs->regmap[HOST_CCREG]!=CCREG) {
      emit_loadreg(CCREG,HOST_CCREG);
    }
    emit_addimm_and_set_flags(CLOCK_DIVIDER*(ccadj[i]+cycles[i]),HOST_CCREG);
    //add_stub(CC_STUB,(int)out,jump_vaddr_reg[slave][t],0,i,-1,TAKEN,0); // FIXME
    //emit_jns(0);
    emit_jmp(jump_vaddr_reg[slave][t]);
  }
}
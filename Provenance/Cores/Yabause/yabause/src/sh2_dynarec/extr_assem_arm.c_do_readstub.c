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
struct regstat {char* regmap; } ;

/* Variables and functions */
 int AGEN1 ; 
 int CCREG ; 
 int LOADB_STUB ; 
 int LOADL_STUB ; 
 int LOADS_STUB ; 
 int LOADW_STUB ; 
 scalar_t__ MappedMemoryReadByte ; 
 scalar_t__ MappedMemoryReadLong ; 
 scalar_t__ MappedMemoryReadWord ; 
 int RTEMP ; 
 int TBIT ; 
 int /*<<< orphan*/  assem_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dynarec_local ; 
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_loadreg (int,int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_movsbl_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_movswl_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_readword (int,int) ; 
 int /*<<< orphan*/  emit_writeword (int,int) ; 
 int /*<<< orphan*/  emit_xorimm (int,int,int /*<<< orphan*/ ) ; 
 int get_reg (char*,int) ; 
 int /*<<< orphan*/  literal_pool (int) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  restore_regs (int) ; 
 int* rt1 ; 
 int /*<<< orphan*/  save_regs (int) ; 
 int /*<<< orphan*/  set_jump_target (int,int) ; 
 scalar_t__ start ; 
 int** stubs ; 

do_readstub(int n)
{
  assem_debug("do_readstub %x\n",start+stubs[n][3]*2);
  literal_pool(256);
  set_jump_target(stubs[n][1],(int)out);
  int type=stubs[n][0];
  int i=stubs[n][3];
  int rs=stubs[n][4];
  struct regstat *i_regs=(struct regstat *)stubs[n][5];
  u32 reglist=stubs[n][7];
  signed char *i_regmap=i_regs->regmap;
  int addr=get_reg(i_regmap,AGEN1+(i&1));
  int rt;
  int ds;

  rt=get_reg(i_regmap,rt1[i]==TBIT?-1:rt1[i]);
  assert(rs>=0);
  if(addr<0) addr=rt;
  if(addr<0) addr=get_reg(i_regmap,-1);
  assert(addr>=0);
  save_regs(reglist);
  if(type==LOADB_STUB) emit_xorimm(rs,1,0);
  else {if(rs!=0) emit_mov(rs,0);}

  //ds=i_regs!=&regs[i];
  //int real_rs=(itype[i]==LOADLR)?-1:get_reg(i_regmap,rs1[i]);
  //u32 cmask=ds?-1:(0x100f|~i_regs->wasdoingcp);
  //if(!ds) load_all_consts(regs[i].regmap_entry,regs[i].was32,regs[i].wasdirty&~(1<<addr)&(real_rs<0?-1:~(1<<real_rs))&0x100f,i);
  //wb_dirtys(i_regs->regmap_entry,i_regs->was32,i_regs->wasdirty&cmask&~(1<<addr)&(real_rs<0?-1:~(1<<real_rs)));
  //if(!ds) wb_consts(regs[i].regmap_entry,regs[i].was32,regs[i].wasdirty&~(1<<addr)&(real_rs<0?-1:~(1<<real_rs))&~0x100f,i);
  int cc=get_reg(i_regmap,CCREG);
  if(cc<0) {
    emit_loadreg(CCREG,2);
  }
  if(type==LOADB_STUB)
    emit_call((int)MappedMemoryReadByte);
  if(type==LOADW_STUB)
    emit_call((int)MappedMemoryReadWord);
  if(type==LOADL_STUB)
    emit_call((int)MappedMemoryReadLong);
  if(type==LOADS_STUB)
  {
    // RTE instruction, pop PC and SR from stack
    int pc=get_reg(i_regmap,RTEMP);
    assert(pc>=0);
    if(rs<4||rs==12)
      emit_writeword(rs,(int)&dynarec_local+24);
    emit_call((int)MappedMemoryReadLong);
    if(rs==1||rs==2||rs==3||rs==12)
      emit_readword((int)&dynarec_local+24,rs);
    if(pc==0) {
      emit_writeword(0,(int)&dynarec_local+24);
    }
    else
    {
      if(pc==1||pc==2||pc==3||pc==12)
        emit_writeword(0,(int)&dynarec_local+24);
      else
        emit_mov(0,pc);
      if(rs==0) {
        emit_readword((int)&dynarec_local+24,rs);
        emit_addimm(rs,4,rs);
      }else
        emit_addimm(rs,4,0);
    }
    emit_call((int)MappedMemoryReadLong);
    assert(rt>=0);
    if(rt!=0) emit_mov(0,rt);
    if(pc<4||pc==12)
      emit_readword((int)&dynarec_local+24,pc);
  }
  else if(type==LOADB_STUB)
  {
    if(rt>=0) emit_movsbl_reg(0,rt);
  }
  else if(type==LOADW_STUB)
  {
    if(rt>=0) emit_movswl_reg(0,rt);
  }
  else
  {
    if(rt>0) emit_mov(0,rt);
  }
  restore_regs(reglist);
  if(type==LOADS_STUB) emit_addimm(rs,8,rs);
  emit_jmp(stubs[n][2]); // return address
}
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
 int EAX ; 
 int ECX ; 
 int EDX ; 
 int /*<<< orphan*/  ESP ; 
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
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_movsbl_reg (int,int) ; 
 int /*<<< orphan*/  emit_movswl_reg (int,int) ; 
 int /*<<< orphan*/  emit_readword_indexed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_writeword_indexed (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_xorimm (int,int,int) ; 
 int get_reg (char*,int) ; 
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
  set_jump_target(stubs[n][1],(int)out);
  int type=stubs[n][0];
  int i=stubs[n][3];
  int rs=stubs[n][4];
  struct regstat *i_regs=(struct regstat *)stubs[n][5];
  u32 reglist=stubs[n][7];
  signed char *i_regmap=i_regs->regmap;
  int addr=get_reg(i_regmap,AGEN1+(i&1));
  int rt;
  
  rt=get_reg(i_regmap,rt1[i]==TBIT?-1:rt1[i]);
  assert(rs>=0);
  if(addr<0) addr=rt;
  if(addr<0) addr=get_reg(i_regmap,-1);
  assert(addr>=0);
  save_regs(reglist);
  if(rs!=EAX) emit_mov(rs,EAX);
  if(type==LOADB_STUB) emit_xorimm(EAX,1,EAX);

  //if(i_regmap[HOST_CCREG]==CCREG) emit_storereg(CCREG,HOST_CCREG);//DEBUG
  /*if(i_regmap[HOST_CCREG]==CCREG) {
    emit_addimm(HOST_CCREG,CLOCK_DIVIDER*(stubs[n][6]),HOST_CCREG);
    output_byte(0x03);
    output_modrm(1,4,HOST_CCREG);
    output_sib(0,4,4);
    output_byte(12+16);
    //emit_writeword(HOST_CCREG,(int)&MSH2->cycles);
    emit_writeword(HOST_CCREG,slave?(int)&SSH2->cycles:(int)&MSH2->cycles);
    output_byte(0x2B);
    output_modrm(1,4,HOST_CCREG);
    output_sib(0,4,4);
    output_byte(12+16);
    emit_addimm(HOST_CCREG,-CLOCK_DIVIDER*(stubs[n][6]),HOST_CCREG);
  }
  if(i_regmap[HOST_CCREG]!=CCREG) {
    emit_loadreg(CCREG,ECX);
    emit_addimm(ECX,CLOCK_DIVIDER*(stubs[n][6]),ECX);
    output_byte(0x03);
    output_modrm(1,4,ECX);
    output_sib(0,4,4);
    output_byte(12+16);
    //emit_writeword(ECX,(int)&MSH2->cycles);
    emit_writeword(ECX,slave?(int)&SSH2->cycles:(int)&MSH2->cycles);
  }
  /*
  int temp;
  int cc=get_reg(i_regmap,CCREG);
  if(cc<0) {
    if(addr==HOST_CCREG)
    {
      cc=0;temp=1;
      assert(cc!=HOST_CCREG);
      assert(temp!=HOST_CCREG);
      emit_loadreg(CCREG,cc);
    }
    else
    {
      cc=HOST_CCREG;
      emit_loadreg(CCREG,cc);
      temp=!addr;
    }
  }
  else
  {
    temp=!addr;
  }*/
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
    if(rs==EAX||rs==ECX||rs==EDX)
      emit_writeword_indexed(rs,0,ESP);
    emit_call((int)MappedMemoryReadLong);
    if(rs==ECX||rs==EDX)
      emit_readword_indexed(0,ESP,rs);
    if(pc==EAX) {
      emit_writeword_indexed(EAX,0,ESP);
    }
    else
    {
      if(pc==ECX||pc==EDX)
        emit_writeword_indexed(EAX,0,ESP);
      else
        emit_mov(EAX,pc);
      if(rs==EAX) {
        emit_readword_indexed(0,ESP,EAX);
        emit_addimm(EAX,4,EAX);
      }else
        emit_addimm(rs,4,EAX);
    }
    emit_call((int)MappedMemoryReadLong);
    assert(rt>=0);
    if(rt!=EAX) emit_mov(EAX,rt);
    if(pc==EAX||pc==ECX||pc==EDX)
      emit_readword_indexed(0,ESP,pc);
  }
  else if(type==LOADB_STUB)
  {
    if(rt>=0) emit_movsbl_reg(EAX,rt);
  }
  else if(type==LOADW_STUB)
  {
    if(rt>=0) emit_movswl_reg(EAX,rt);
  }
  else
  {
    if(rt!=EAX&&rt>=0) emit_mov(EAX,rt);
  }
  restore_regs(reglist);
  if(type==LOADS_STUB) emit_addimm(rs,8,rs);
  emit_jmp(stubs[n][2]); // return address
}
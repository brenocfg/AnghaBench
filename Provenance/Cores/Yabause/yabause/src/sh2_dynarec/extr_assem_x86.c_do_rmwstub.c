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
typedef  int /*<<< orphan*/  pointer ;

/* Variables and functions */
 int AGEN1 ; 
 int EAX ; 
 int ECX ; 
 int EDX ; 
 int /*<<< orphan*/  ESP ; 
 scalar_t__ MappedMemoryReadByte ; 
 int RMWA_STUB ; 
 int RMWO_STUB ; 
 int RMWT_STUB ; 
 int RMWX_STUB ; 
 int SR ; 
 scalar_t__ WriteInvalidateByte ; 
 int /*<<< orphan*/  assem_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_adcimm (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  emit_andimm (char,int,char) ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_cmpmem_imm_byte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_orimm (int,int,int) ; 
 int /*<<< orphan*/  emit_readword_indexed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_writeword (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_writeword_indexed (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_xorimm (int,int,int) ; 
 void* get_reg (char*,int) ; 
 int* imm ; 
 int* opcode2 ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  restore_regs (int) ; 
 int /*<<< orphan*/  rmw_temp ; 
 int /*<<< orphan*/  save_regs (int) ; 
 int /*<<< orphan*/  set_jump_target (int,int) ; 
 scalar_t__ start ; 
 int** stubs ; 

do_rmwstub(int n)
{
  assem_debug("do_rmwstub %x\n",start+stubs[n][3]*2);
  set_jump_target(stubs[n][1],(int)out);
  int type=stubs[n][0];
  int i=stubs[n][3];
  int rs=stubs[n][4];
  struct regstat *i_regs=(struct regstat *)stubs[n][5];
  u32 reglist=stubs[n][7];
  signed char *i_regmap=i_regs->regmap;
  int addr=get_reg(i_regmap,AGEN1+(i&1));
  //int rt=get_reg(i_regmap,rs1[i]);
  assert(rs>=0);
  //assert(rt>=0);
  if(addr<0) addr=get_reg(i_regmap,-1);
  assert(addr>=0);
  save_regs(reglist);
  // "FASTCALL" api: address in eax, data in edx
  emit_xorimm(rs,1,rs);
  if(rs!=EAX) emit_mov(rs,EAX);
  if(rs==EAX||rs==ECX||rs==EDX)
    emit_writeword_indexed(rs,0,ESP);
  
  //if(i_regmap[HOST_CCREG]==CCREG) emit_storereg(CCREG,HOST_CCREG);//DEBUG
  /*if(i_regmap[HOST_CCREG]==CCREG) {
    emit_addimm(HOST_CCREG,CLOCK_DIVIDER*(stubs[n][6]),HOST_CCREG);
    output_byte(0x03);
    output_modrm(1,4,HOST_CCREG);
    output_sib(0,4,4);
    output_byte(12+16);
    emit_writeword(HOST_CCREG,(int)&MSH2->cycles);
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
    emit_writeword(ECX,(int)&MSH2->cycles);
  }*/
  emit_call((int)MappedMemoryReadByte);
  emit_mov(EAX,EDX);
  if(rs==EAX||rs==ECX||rs==EDX)
    emit_readword_indexed(0,ESP,EAX);
  else
    emit_mov(rs,EAX);
  if(type==RMWA_STUB)
    emit_andimm(EDX,imm[i],EDX);
  if(type==RMWX_STUB)
    emit_xorimm(EDX,imm[i],EDX);
  if(type==RMWO_STUB)
    emit_orimm(EDX,imm[i],EDX);
  if(type==RMWT_STUB) { // TAS.B
    //emit_writeword_indexed(EDX,0,ESP);
    emit_writeword(EDX,(pointer)&rmw_temp);
    emit_orimm(EDX,0x80,EDX);
  }
  //emit_call((int)MappedMemoryWriteByte);
  emit_call((int)WriteInvalidateByte);
  
  restore_regs(reglist);

  if(opcode2[i]==11) { // TAS.B
    signed char sr;
    sr=get_reg(i_regs->regmap,SR);
    assert(sr>=0); // Liveness analysis?
    emit_andimm(sr,~1,sr);
    //assem_debug("cmp $%d,%d+%%%s\n",1,-16,regname[ESP]);
    //output_byte(0x80);
    //output_modrm(1,4,7);
    //output_sib(0,4,4);
    //output_byte(-16);
    //output_byte(1);
    emit_cmpmem_imm_byte((pointer)&rmw_temp,1);
    emit_adcimm(0,sr);
  }
  emit_jmp(stubs[n][2]); // return address
}
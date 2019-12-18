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
 scalar_t__ MappedMemoryReadByte ; 
 int RMWA_STUB ; 
 int RMWO_STUB ; 
 int RMWT_STUB ; 
 int RMWX_STUB ; 
 int SR ; 
 scalar_t__ WriteInvalidateByte ; 
 int /*<<< orphan*/  assem_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dynarec_local ; 
 int /*<<< orphan*/  emit_andimm (char,int,char) ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_mov (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_orimm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_orreq_imm (char,int,char) ; 
 int /*<<< orphan*/  emit_readword (int,int) ; 
 int /*<<< orphan*/  emit_testimm (int,int) ; 
 int /*<<< orphan*/  emit_writeword (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_xorimm (int,int,int) ; 
 void* get_reg (char*,int) ; 
 int* imm ; 
 int* opcode2 ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  restore_regs (int) ; 
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
  // "FASTCALL" api: address in r0, data in r1 
  emit_xorimm(rs,1,rs);
  if(rs!=0) emit_mov(rs,0);
  if(rs<4||rs==12)
    emit_writeword(0,(int)&dynarec_local+24);
  
  //if(i_regmap[HOST_CCREG]==CCREG) emit_storereg(CCREG,HOST_CCREG);//DEBUG
  emit_call((int)MappedMemoryReadByte);
  //emit_mov(0,1);
  if(type==RMWA_STUB)
    emit_andimm(0,imm[i],1);
  if(type==RMWX_STUB)
    emit_xorimm(0,imm[i],1);
  if(type==RMWO_STUB)
    emit_orimm(0,imm[i],1);
  if(type==RMWT_STUB) { // TAS.B
    emit_writeword(0,(int)&dynarec_local+20);
    emit_orimm(0,0x80,1);
  }
  if(rs<4||rs==12)
    emit_readword((int)&dynarec_local+24,0);
  else
    emit_mov(rs,0);
  //emit_call((int)MappedMemoryWriteByte);
  emit_call((int)WriteInvalidateByte);
  
  restore_regs(reglist);

  if(opcode2[i]==11) { // TAS.B
    emit_readword((int)&dynarec_local+20,14);
    signed char sr;
    sr=get_reg(i_regs->regmap,SR);
    assert(sr>=0); // Liveness analysis?
    emit_andimm(sr,~1,sr);
    emit_testimm(14,0xff);
    emit_orreq_imm(sr,1,sr);
  }
  emit_jmp(stubs[n][2]); // return address
}
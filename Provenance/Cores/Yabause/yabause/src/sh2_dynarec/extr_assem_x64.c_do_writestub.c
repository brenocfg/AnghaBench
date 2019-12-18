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
 int EDI ; 
 int ESI ; 
 int STOREB_STUB ; 
 int STOREL_STUB ; 
 int STOREW_STUB ; 
 scalar_t__ WriteInvalidateByteSwapped ; 
 scalar_t__ WriteInvalidateLong ; 
 scalar_t__ WriteInvalidateWord ; 
 int /*<<< orphan*/  assem_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_xchg (int,int) ; 
 int get_reg (char*,int) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  restore_regs (int) ; 
 int* rs1 ; 
 int /*<<< orphan*/  save_regs (int) ; 
 int /*<<< orphan*/  set_jump_target (int,int) ; 
 scalar_t__ start ; 
 int** stubs ; 

do_writestub(int n)
{
  assem_debug("do_writestub %x\n",start+stubs[n][3]*2);
  set_jump_target(stubs[n][1],(int)out);
  int type=stubs[n][0];
  int i=stubs[n][3];
  int rs=stubs[n][4];
  struct regstat *i_regs=(struct regstat *)stubs[n][5];
  u32 reglist=stubs[n][7];
  signed char *i_regmap=i_regs->regmap;
  int addr=get_reg(i_regmap,AGEN1+(i&1));
  int rt=get_reg(i_regmap,rs1[i]);
  assert(rs>=0);
  assert(rt>=0);
  if(addr<0) addr=get_reg(i_regmap,-1);
  assert(addr>=0);
  save_regs(reglist);
  // "FASTCALL" api: address in edi, data in esi
  if(rs!=EDI) {
    if(rt==EDI) {
      if(rs==ESI) emit_xchg(EDI,ESI);
      else {
        emit_mov(rt,ESI);
        emit_mov(rs,EDI);
      }
    }
    else {
      emit_mov(rs,EDI);
      if(rt!=ESI) emit_mov(rt,ESI);
    }
  }
  else if(rt!=ESI) emit_mov(rt,ESI);
  //if(type==STOREB_STUB) emit_xorimm(EAX,1,EAX); // WriteInvalidateByteSwapped does this
  
  /*int temp;
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
  if(type==STOREB_STUB)
    emit_call((int)WriteInvalidateByteSwapped);
  if(type==STOREW_STUB)
    emit_call((int)WriteInvalidateWord);
  if(type==STOREL_STUB)
    emit_call((int)WriteInvalidateLong);
  
  restore_regs(reglist);
  emit_jmp(stubs[n][2]); // return address
}
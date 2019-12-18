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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EAX ; 
 int LOADB_STUB ; 
 int LOADL_STUB ; 
 int LOADS_STUB ; 
 int LOADW_STUB ; 
 scalar_t__ MappedMemoryReadByte ; 
 scalar_t__ MappedMemoryReadLong ; 
 scalar_t__ MappedMemoryReadWord ; 
 int /*<<< orphan*/  assem_debug (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_movimm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_movsbl_reg (int,int) ; 
 int /*<<< orphan*/  emit_movswl_reg (int,int) ; 
 int get_reg (char*,int) ; 
 int /*<<< orphan*/  restore_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_regs (int /*<<< orphan*/ ) ; 

inline_readstub(int type, int i, u32 addr, signed char regmap[], int target, int adj, u32 reglist)
{
  assem_debug("inline_readstub\n");
  //int rs=get_reg(regmap,target);
  int rt=get_reg(regmap,target);
  //if(rs<0) rs=get_reg(regmap,-1);
  if(rt<0) rt=get_reg(regmap,-1);
  //rt=get_reg(i_regmap,rt1[i]==TBIT?-1:rt1[i]);
  assert(rt>=0);
  //if(addr<0) addr=rt;
  //if(addr<0) addr=get_reg(i_regmap,-1);
  //assert(addr>=0);
  save_regs(reglist);
  emit_movimm(addr,EAX);
  if(type==LOADB_STUB)
    emit_call((int)MappedMemoryReadByte);
  if(type==LOADW_STUB)
    emit_call((int)MappedMemoryReadWord);
  if(type==LOADL_STUB)
    emit_call((int)MappedMemoryReadLong);
  assert(type!=LOADS_STUB);
  if(type==LOADB_STUB)
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
}
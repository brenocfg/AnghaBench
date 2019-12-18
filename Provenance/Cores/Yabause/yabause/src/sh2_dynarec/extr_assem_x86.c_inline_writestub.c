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
 int /*<<< orphan*/  EAX ; 
 int EDX ; 
 int STOREB_STUB ; 
 int STOREL_STUB ; 
 int STOREW_STUB ; 
 scalar_t__ WriteInvalidateByte ; 
 scalar_t__ WriteInvalidateLong ; 
 scalar_t__ WriteInvalidateWord ; 
 int /*<<< orphan*/  assem_debug (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_movimm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_reg (char*,int) ; 
 int /*<<< orphan*/  restore_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_regs (int /*<<< orphan*/ ) ; 

inline_writestub(int type, int i, u32 addr, signed char regmap[], int target, int adj, u32 reglist)
{
  assem_debug("inline_writestub\n");
  //int rs=get_reg(regmap,-1);
  int rt=get_reg(regmap,target);
  //assert(rs>=0);
  assert(rt>=0);
  save_regs(reglist);
  // "FASTCALL" api: address in eax, data in edx
  if(rt!=EDX) emit_mov(rt,EDX);
  emit_movimm(addr,EAX); // FIXME - should be able to move the existing value
  if(type==STOREB_STUB)
    emit_call((int)WriteInvalidateByte);
  if(type==STOREW_STUB)
    emit_call((int)WriteInvalidateWord);
  if(type==STOREL_STUB)
    emit_call((int)WriteInvalidateLong);
  restore_regs(reglist);
}
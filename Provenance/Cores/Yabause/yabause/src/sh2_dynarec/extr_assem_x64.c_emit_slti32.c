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

/* Variables and functions */
 int /*<<< orphan*/  const_one ; 
 int /*<<< orphan*/  emit_cmovl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_cmpimm (int,int) ; 
 int /*<<< orphan*/  emit_movimm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_movzbl_reg (int,int) ; 
 int /*<<< orphan*/  emit_setl (int) ; 
 int /*<<< orphan*/  emit_zeroreg (int) ; 

void emit_slti32(int rs,int imm,int rt)
{
  if(rs!=rt) emit_zeroreg(rt);
  emit_cmpimm(rs,imm);
  if(rt<4) {
    emit_setl(rt);
    if(rs==rt) emit_movzbl_reg(rt,rt);
  }
  else
  {
    if(rs==rt) emit_movimm(0,rt);
    emit_cmovl(&const_one,rt);
  }
}
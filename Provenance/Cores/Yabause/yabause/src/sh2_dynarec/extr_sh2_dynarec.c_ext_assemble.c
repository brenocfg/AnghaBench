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
struct regstat {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  emit_loadreg (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  emit_movsbl_reg (char,char) ; 
 int /*<<< orphan*/  emit_movswl_reg (char,char) ; 
 int /*<<< orphan*/  emit_movzbl_reg (char,char) ; 
 int /*<<< orphan*/  emit_movzwl_reg (char,char) ; 
 char get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* opcode2 ; 
 int /*<<< orphan*/ * rs1 ; 
 int /*<<< orphan*/ * rt1 ; 

void ext_assemble(int i,struct regstat *i_regs)
{
  signed char s,t;
  t=get_reg(i_regs->regmap,rt1[i]);
  //assert(t>=0);
  if(t>=0) {
    s=get_reg(i_regs->regmap,rs1[i]);
    if(s>=0) {
      if(opcode2[i]==12) emit_movzbl_reg(s,t);
      if(opcode2[i]==13) emit_movzwl_reg(s,t);
      if(opcode2[i]==14) emit_movsbl_reg(s,t);
      if(opcode2[i]==15) emit_movswl_reg(s,t);
    }
    else
    {
      emit_loadreg(rs1[i],t); // Fix - do byte/halfword loads?
      if(opcode2[i]==12) emit_movzbl_reg(t,t);
      if(opcode2[i]==13) emit_movzwl_reg(t,t);
      if(opcode2[i]==14) emit_movsbl_reg(t,t);
      if(opcode2[i]==15) emit_movswl_reg(t,t);
    }
  }
}
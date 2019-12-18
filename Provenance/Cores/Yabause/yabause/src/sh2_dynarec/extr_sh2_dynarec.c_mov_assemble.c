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
 int /*<<< orphan*/  emit_mov (char,char) ; 
 char get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rs1 ; 
 int /*<<< orphan*/ * rt1 ; 

void mov_assemble(int i,struct regstat *i_regs)
{
  signed char s,t;
  t=get_reg(i_regs->regmap,rt1[i]);
  //assert(t>=0);
  if(t>=0) {
    s=get_reg(i_regs->regmap,rs1[i]);
    if(s>=0) {if(s!=t) emit_mov(s,t);}
    else emit_loadreg(rs1[i],t);
  }
}
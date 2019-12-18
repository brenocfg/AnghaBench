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
 int /*<<< orphan*/  assem_debug (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_sarimm (int,int,int) ; 
 int /*<<< orphan*/  emit_shlimm (int,int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 scalar_t__* regname ; 

void emit_movsbl_reg(int rs, int rt)
{
  if(rs<4) {
    assem_debug("movsbl %%%s,%%%s\n",regname[rs]+1,regname[rt]);
    output_byte(0x0F);
    output_byte(0xBE);
    output_modrm(3,rs,rt);
  }
  else if(rt<4) {
    emit_mov(rs,rt);
    emit_movsbl_reg(rt,rt);
  }
  else {
    emit_shlimm(rs,24,rt);
    emit_sarimm(rt,24,rt);
  }
}
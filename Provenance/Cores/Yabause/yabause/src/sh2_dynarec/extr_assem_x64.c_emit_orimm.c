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
 int /*<<< orphan*/  assem_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_orimm(int rs,int imm,int rt)
{
  if(rs==rt) {
    if(imm!=0) {
      assem_debug("or $%d,%%%s\n",imm,regname[rt]);
      if(imm<128&&imm>=-128) {
        output_byte(0x83);
        output_modrm(3,rt,1);
        output_byte(imm);
      }
      else
      {
        output_byte(0x81);
        output_modrm(3,rt,1);
        output_w32(imm);
      }
    }
  }
  else {
    emit_mov(rs,rt);
    emit_orimm(rt,imm,rt);
  }
}
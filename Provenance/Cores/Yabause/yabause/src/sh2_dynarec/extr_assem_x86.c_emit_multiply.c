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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_multiply(int rs1,int rs2,int rt)
{
  if(rs1==rt) {
    assem_debug("imul %%%s,%%%s\n",regname[rs2],regname[rt]);
    output_byte(0x0F);
    output_byte(0xAF);
    output_modrm(3,rs2,rt);
  }
  else
  {
    emit_mov(rs1,rt);
    emit_multiply(rt,rs2,rt);
  }
}
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
 int EBP ; 
 int /*<<< orphan*/  assem_debug (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_sib (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_leairrx4(int imm,int rs1,int rs2,int rt)
{
  assem_debug("lea %x(%%%s,%%%s,4),%%%s\n",imm,regname[rs1],regname[rs2],regname[rt]);
  output_byte(0x8D);
  if(imm!=0||rs1==EBP) {
    output_modrm(2,4,rt);
    output_sib(2,rs2,rs1);
    output_w32(imm);
  }else{
    output_modrm(0,4,rt);
    output_sib(2,rs2,rs1);
  }
}
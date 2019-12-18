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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_sib (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_add(int rs1,int rs2,int rt)
{
  if(rs1==rt) {
    assem_debug("add %%%s,%%%s\n",regname[rs2],regname[rs1]);
    output_byte(0x01);
    output_modrm(3,rs1,rs2);
  }else if(rs2==rt) {
    assem_debug("add %%%s,%%%s\n",regname[rs1],regname[rs2]);
    output_byte(0x01);
    output_modrm(3,rs2,rs1);
  }else {
    assem_debug("lea (%%%s,%%%s),%%%s\n",regname[rs1],regname[rs2],regname[rt]);
    output_byte(0x8D);
    if(rs1!=EBP) {
      output_modrm(0,4,rt);
      output_sib(0,rs2,rs1);
    }else if(rs2!=EBP) {
      output_modrm(0,4,rt);
      output_sib(0,rs1,rs2);
    }else /* lea 0(,%ebp,2) */{
      output_modrm(0,4,rt);
      output_sib(1,EBP,5);
      output_w32(0);
    }
  }
}
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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int,int,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_shldimm(int rs,int rs2,unsigned int imm,int rt)
{
  assem_debug("shld %%%s,%%%s,%d\n",regname[rt],regname[rs2],imm);
  assert(imm>0);
  assert(imm<32);
  //if(imm==1) ...
  assem_debug("lsl %s,%s,#%d\n",regname[rt],regname[rs],imm);
  output_w32(0xe1a00000|rd_rn_rm(rt,0,rs)|(imm<<7));
  assem_debug("orr %s,%s,%s,lsr #%d\n",regname[rt],regname[rt],regname[rs2],32-imm);
  output_w32(0xe1800020|rd_rn_rm(rt,rt,rs2)|((32-imm)<<7));
}
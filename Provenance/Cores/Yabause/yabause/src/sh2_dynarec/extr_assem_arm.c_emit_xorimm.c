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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 scalar_t__ genimm (int,int*) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_imm_shift (int,int,int,int) ; 
 int rd_rn_rm (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_xorimm(int rs,int imm,int rt)
{
  u32 armval;
  if(imm==0) {
    if(rs!=rt) emit_mov(rs,rt);
  }else if(genimm(imm,&armval)) {
    assem_debug("eor %s,%s,#%d\n",regname[rt],regname[rs],imm);
    output_w32(0xe2200000|rd_rn_rm(rt,rs,0)|armval);
  }else{
    assert(imm>0&&imm<65536);
    assem_debug("eor %s,%s,#%d\n",regname[rt],regname[rs],imm&0xFF00);
    assem_debug("eor %s,%s,#%d\n",regname[rt],regname[rs],imm&0xFF);
    output_w32(0xe2200000|rd_rn_imm_shift(rt,rs,imm>>8,8));
    output_w32(0xe2200000|rd_rn_imm_shift(rt,rt,imm&0xff,0));
  }
}
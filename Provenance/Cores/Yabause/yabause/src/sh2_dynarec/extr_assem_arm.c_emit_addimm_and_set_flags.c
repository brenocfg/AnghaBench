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
 scalar_t__ genimm (int,int*) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_imm_shift (int,int,int,int) ; 
 int rd_rn_rm (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_addimm_and_set_flags(int imm,int rt)
{
  assert(imm>-65536&&imm<65536);
  u32 armval;
  if(genimm(imm,&armval)) {
    assem_debug("adds %s,%s,#%d\n",regname[rt],regname[rt],imm);
    output_w32(0xe2900000|rd_rn_rm(rt,rt,0)|armval);
  }else if(genimm(-imm,&armval)) {
    assem_debug("subs %s,%s,#%d\n",regname[rt],regname[rt],imm);
    output_w32(0xe2500000|rd_rn_rm(rt,rt,0)|armval);
  }else if(imm<0) {
    assem_debug("sub %s,%s,#%d\n",regname[rt],regname[rt],(-imm)&0xFF00);
    assem_debug("subs %s,%s,#%d\n",regname[rt],regname[rt],(-imm)&0xFF);
    output_w32(0xe2400000|rd_rn_imm_shift(rt,rt,(-imm)>>8,8));
    output_w32(0xe2500000|rd_rn_imm_shift(rt,rt,(-imm)&0xff,0));
  }else{
    assem_debug("add %s,%s,#%d\n",regname[rt],regname[rt],imm&0xFF00);
    assem_debug("adds %s,%s,#%d\n",regname[rt],regname[rt],imm&0xFF);
    output_w32(0xe2800000|rd_rn_imm_shift(rt,rt,imm>>8,8));
    output_w32(0xe2900000|rd_rn_imm_shift(rt,rt,imm&0xff,0));
  }
}
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
 int /*<<< orphan*/  emit_mov (unsigned int,unsigned int) ; 
 scalar_t__ genimm (int,int*) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_imm_shift (unsigned int,unsigned int,int,int) ; 
 int rd_rn_rm (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_addimm(unsigned int rs,int imm,unsigned int rt)
{
  assert(rs<16);
  assert(rt<16);
  if(imm!=0) {
    assert(imm>-65536&&imm<65536);
    u32 armval;
    if(genimm(imm,&armval)) {
      assem_debug("add %s,%s,#%d\n",regname[rt],regname[rs],imm);
      output_w32(0xe2800000|rd_rn_rm(rt,rs,0)|armval);
    }else if(genimm(-imm,&armval)) {
      assem_debug("sub %s,%s,#%d\n",regname[rt],regname[rs],imm);
      output_w32(0xe2400000|rd_rn_rm(rt,rs,0)|armval);
    }else if(imm<0) {
      assem_debug("sub %s,%s,#%d\n",regname[rt],regname[rs],(-imm)&0xFF00);
      assem_debug("sub %s,%s,#%d\n",regname[rt],regname[rt],(-imm)&0xFF);
      output_w32(0xe2400000|rd_rn_imm_shift(rt,rs,(-imm)>>8,8));
      output_w32(0xe2400000|rd_rn_imm_shift(rt,rt,(-imm)&0xff,0));
    }else{
      assem_debug("add %s,%s,#%d\n",regname[rt],regname[rs],imm&0xFF00);
      assem_debug("add %s,%s,#%d\n",regname[rt],regname[rt],imm&0xFF);
      output_w32(0xe2800000|rd_rn_imm_shift(rt,rs,imm>>8,8));
      output_w32(0xe2800000|rd_rn_imm_shift(rt,rt,imm&0xff,0));
    }
  }
  else if(rs!=rt) emit_mov(rs,rt);
}
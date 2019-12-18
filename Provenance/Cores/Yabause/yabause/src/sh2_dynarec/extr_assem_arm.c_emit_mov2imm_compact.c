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
 int /*<<< orphan*/  emit_movimm (int,unsigned int) ; 
 scalar_t__ genimm (int,int*) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_mov2imm_compact(int imm1,unsigned int rt1,int imm2,unsigned int rt2)
{
  emit_movimm(imm1,rt1);
  u32 armval;
  if(genimm(imm2-imm1,&armval)) {
    assem_debug("add %s,%s,#%d\n",regname[rt2],regname[rt1],imm2-imm1);
    output_w32(0xe2800000|rd_rn_rm(rt2,rt1,0)|armval);
  }else if(genimm(imm1-imm2,&armval)) {
    assem_debug("sub %s,%s,#%d\n",regname[rt2],regname[rt1],imm1-imm2);
    output_w32(0xe2400000|rd_rn_rm(rt2,rt1,0)|armval);
  }
  else emit_movimm(imm2,rt2);
}
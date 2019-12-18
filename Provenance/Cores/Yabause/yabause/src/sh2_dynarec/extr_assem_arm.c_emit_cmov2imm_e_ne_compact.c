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
 int /*<<< orphan*/  add_literal (int,int) ; 
 int /*<<< orphan*/  assem_debug (char*,int,int,...) ; 
 int /*<<< orphan*/  emit_movimm (int,unsigned int) ; 
 int /*<<< orphan*/  emit_movt (int,unsigned int) ; 
 int /*<<< orphan*/  emit_movw (int,unsigned int) ; 
 scalar_t__ genimm (int,int*) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (unsigned int,int,int /*<<< orphan*/ ) ; 
 int* regname ; 

void emit_cmov2imm_e_ne_compact(int imm1,int imm2,unsigned int rt)
{
  u32 armval;
  if(genimm(imm2-imm1,&armval)) {
    emit_movimm(imm1,rt);
    assem_debug("addne %s,%s,#%d\n",regname[rt],regname[rt],imm2-imm1);
    output_w32(0x12800000|rd_rn_rm(rt,rt,0)|armval);
  }else if(genimm(imm1-imm2,&armval)) {
    emit_movimm(imm1,rt);
    assem_debug("subne %s,%s,#%d\n",regname[rt],regname[rt],imm1-imm2);
    output_w32(0x12400000|rd_rn_rm(rt,rt,0)|armval);
  }
  else {
    #ifndef HAVE_ARMv7
    emit_movimm(imm1,rt);
    add_literal((int)out,imm2);
    assem_debug("ldrne %s,pc+? [=%x]\n",regname[rt],imm2);
    output_w32(0x15900000|rd_rn_rm(rt,15,0));
    #else
    emit_movw(imm1&0x0000FFFF,rt);
    if((imm1&0xFFFF)!=(imm2&0xFFFF)) {
      assem_debug("movwne %s,#%d (0x%x)\n",regname[rt],imm2&0xFFFF,imm2&0xFFFF);
      output_w32(0x13000000|rd_rn_rm(rt,0,0)|(imm2&0xfff)|((imm2<<4)&0xf0000));
    }
    emit_movt(imm1&0xFFFF0000,rt);
    if((imm1&0xFFFF0000)!=(imm2&0xFFFF0000)) {
      assem_debug("movtne %s,#%d (0x%x)\n",regname[rt],imm2&0xffff0000,imm2&0xffff0000);
      output_w32(0x13400000|rd_rn_rm(rt,0,0)|((imm2>>16)&0xfff)|((imm2>>12)&0xf0000));
    }
    #endif
  }
}
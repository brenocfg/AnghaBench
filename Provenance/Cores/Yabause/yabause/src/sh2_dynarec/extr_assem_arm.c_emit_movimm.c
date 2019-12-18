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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  emit_loadlp (int,unsigned int) ; 
 int /*<<< orphan*/  emit_movt (int,unsigned int) ; 
 int /*<<< orphan*/  emit_movw (int,unsigned int) ; 
 scalar_t__ genimm (int,int*) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_imm_shift (unsigned int,unsigned int,int,int) ; 
 int rd_rn_rm (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movimm(u32 imm,unsigned int rt)
{
  u32 armval;
  if(genimm(imm,&armval)) {
    assem_debug("mov %s,#%d\n",regname[rt],imm);
    output_w32(0xe3a00000|rd_rn_rm(rt,0,0)|armval);
  }else if(genimm(~imm,&armval)) {
    assem_debug("mvn %s,#%d\n",regname[rt],imm);
    output_w32(0xe3e00000|rd_rn_rm(rt,0,0)|armval);
  }else if(imm<65536) {
    #ifndef HAVE_ARMv7
    assem_debug("mov %s,#%d\n",regname[rt],imm&0xFF00);
    output_w32(0xe3a00000|rd_rn_imm_shift(rt,0,imm>>8,8));
    assem_debug("add %s,%s,#%d\n",regname[rt],regname[rt],imm&0xFF);
    output_w32(0xe2800000|rd_rn_imm_shift(rt,rt,imm&0xff,0));
    #else
    emit_movw(imm,rt);
    #endif
  }else{
    #ifndef HAVE_ARMv7
    emit_loadlp(imm,rt);
    #else
    emit_movw(imm&0x0000FFFF,rt);
    emit_movt(imm&0xFFFF0000,rt);
    #endif
  }
}
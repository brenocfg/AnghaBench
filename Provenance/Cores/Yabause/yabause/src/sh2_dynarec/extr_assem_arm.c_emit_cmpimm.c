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
 int /*<<< orphan*/  HOST_TEMPREG ; 
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_movimm (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_movw (int,int /*<<< orphan*/ ) ; 
 scalar_t__ genimm (int,int*) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_cmpimm(int rs,int imm)
{
  u32 armval;
  if(genimm(imm,&armval)) {
    assem_debug("cmp %s,#%d\n",regname[rs],imm);
    output_w32(0xe3500000|rd_rn_rm(0,rs,0)|armval);
  }else if(genimm(-imm,&armval)) {
    assem_debug("cmn %s,#%d\n",regname[rs],imm);
    output_w32(0xe3700000|rd_rn_rm(0,rs,0)|armval);
  }else if(imm>0) {
    assert(imm<65536);
    #ifndef HAVE_ARMv7
    emit_movimm(imm,HOST_TEMPREG);
    #else
    emit_movw(imm,HOST_TEMPREG);
    #endif
    assem_debug("cmp %s,r14\n",regname[rs]);
    output_w32(0xe1500000|rd_rn_rm(0,rs,HOST_TEMPREG));
  }else{
    assert(imm>-65536);
    #ifndef HAVE_ARMv7
    emit_movimm(-imm,HOST_TEMPREG);
    #else
    emit_movw(-imm,HOST_TEMPREG);
    #endif
    assem_debug("cmn %s,r14\n",regname[rs]);
    output_w32(0xe1700000|rd_rn_rm(0,rs,HOST_TEMPREG));
  }
}
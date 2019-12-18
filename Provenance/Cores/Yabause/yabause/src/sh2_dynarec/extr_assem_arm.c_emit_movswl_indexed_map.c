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
 size_t HOST_TEMPREG ; 
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_movswl_indexed (int,int,int) ; 
 int /*<<< orphan*/  emit_shlimm (int,int,size_t) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int,int,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movswl_indexed_map(int addr, int rs, int map, int rt)
{
  if(map<0) emit_movswl_indexed(addr, rs, rt);
  else {
    if(addr==0) {
      emit_shlimm(map,2,HOST_TEMPREG);
      assem_debug("ldrsh %s,%s+%s\n",regname[rt],regname[rs],regname[HOST_TEMPREG]);
      output_w32(0xe19000f0|rd_rn_rm(rt,rs,HOST_TEMPREG));
    }else{
      assert(addr>-256&&addr<256);
      assem_debug("add %s,%s,%s,lsl #2\n",regname[rt],regname[rs],regname[map]);
      output_w32(0xe0800000|rd_rn_rm(rt,rs,map)|(2<<7));
      emit_movswl_indexed(addr, rt, rt);
    }
  }
}
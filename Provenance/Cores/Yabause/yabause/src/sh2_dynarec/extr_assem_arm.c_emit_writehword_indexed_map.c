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
 int /*<<< orphan*/  emit_shlimm (int,int,size_t) ; 
 int /*<<< orphan*/  emit_writehword_indexed (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int,int,size_t) ; 
 int /*<<< orphan*/ * regname ; 

void emit_writehword_indexed_map(int rt, int addr, int rs, int map, int temp)
{
  if(map<0) emit_writehword_indexed(rt, addr, rs);
  else {
    if(addr==0) {
      emit_shlimm(map,2,HOST_TEMPREG);
      assem_debug("strh %s,%s+%s\n",regname[rt],regname[rs],regname[HOST_TEMPREG]);
      output_w32(0xe18000b0|rd_rn_rm(rt,rs,HOST_TEMPREG));
    }else{
      assert(addr==0);
    }
  }
}
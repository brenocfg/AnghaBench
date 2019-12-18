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
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_writebyte_dualindexedx4 (int,int,int) ; 
 int /*<<< orphan*/  emit_writebyte_indexed (int,int,int) ; 

void emit_writebyte_indexed_map(int rt, int addr, int rs, int map, int temp)
{
  if(map<0) emit_writebyte_indexed(rt, addr, rs);
  else {
    if(addr==0) {
      emit_writebyte_dualindexedx4(rt, rs, map);
    }else{
      emit_addimm(rs,addr,temp);
      emit_writebyte_dualindexedx4(rt, temp, map);
    }
  }
}
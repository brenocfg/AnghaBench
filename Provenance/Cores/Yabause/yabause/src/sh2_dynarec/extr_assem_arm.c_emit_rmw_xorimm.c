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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_movzbl_dualindexedx4 (int,int,int) ; 
 int /*<<< orphan*/  emit_writebyte_dualindexedx4 (int,int,int) ; 
 int /*<<< orphan*/  emit_xorimm (int,int,int) ; 

void emit_rmw_xorimm(int addr, int map, int imm)
{
  if(map<0) {
    assert(map>=0);
  }
  else
  {
    emit_movzbl_dualindexedx4(addr, map, 14);
    emit_xorimm(14,imm,14);
    emit_writebyte_dualindexedx4(14, addr, map);
  }
}
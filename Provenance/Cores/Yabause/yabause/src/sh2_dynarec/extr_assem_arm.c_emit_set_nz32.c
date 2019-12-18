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
 int /*<<< orphan*/  emit_cmovne_imm (int,int) ; 
 int /*<<< orphan*/  emit_movs (int,int) ; 
 int /*<<< orphan*/  emit_test (int,int) ; 

void emit_set_nz32(int rs, int rt)
{
  //assem_debug("set_nz32\n");
  if(rs!=rt) emit_movs(rs,rt);
  else emit_test(rs,rs);
  emit_cmovne_imm(1,rt);
}
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
 int /*<<< orphan*/  const_zero ; 
 int /*<<< orphan*/  emit_cmovl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_cmpimm (int,int) ; 
 int /*<<< orphan*/  emit_movimm (int,int) ; 

void emit_set_gz32(int rs, int rt)
{
  //assem_debug("set_gz32\n");
  emit_cmpimm(rs,1);
  emit_movimm(1,rt);
  emit_cmovl(&const_zero,rt);
}
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
 int /*<<< orphan*/  emit_or_and_set_flags (int,int,int) ; 

void emit_set_nz64_32(int rsh, int rsl, int rt)
{
  //assem_debug("set_nz64\n");
  emit_or_and_set_flags(rsh,rsl,rt);
  emit_cmovne_imm(1,rt);
}
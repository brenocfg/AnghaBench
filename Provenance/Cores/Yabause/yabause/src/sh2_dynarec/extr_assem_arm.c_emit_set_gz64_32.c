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
 int /*<<< orphan*/  emit_cmovs_imm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_set_gz32 (int,int) ; 
 int /*<<< orphan*/  emit_test (int,int) ; 

void emit_set_gz64_32(int rsh, int rsl, int rt)
{
  //assem_debug("set_gz64\n");
  emit_set_gz32(rsl,rt);
  emit_test(rsh,rsh);
  emit_cmovne_imm(1,rt);
  emit_cmovs_imm(0,rt);
}
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
 int /*<<< orphan*/  const_one ; 
 int /*<<< orphan*/  const_zero ; 
 int /*<<< orphan*/  emit_cmovl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_cmovne (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_cmovs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emit_cmpimm (int,int) ; 
 int /*<<< orphan*/  emit_slti32 (int,int,int) ; 
 int /*<<< orphan*/  emit_test (int,int) ; 

void emit_slti64_32(int rsh,int rsl,int imm,int rt)
{
  assert(rsh!=rt);
  emit_slti32(rsl,imm,rt);
  if(imm>=0)
  {
    emit_test(rsh,rsh);
    emit_cmovne(&const_zero,rt);
    emit_cmovs(&const_one,rt);
  }
  else
  {
    emit_cmpimm(rsh,-1);
    emit_cmovne(&const_zero,rt);
    emit_cmovl(&const_one,rt);
  }
}
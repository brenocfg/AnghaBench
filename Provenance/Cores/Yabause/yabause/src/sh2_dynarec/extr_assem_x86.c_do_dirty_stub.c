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
 int /*<<< orphan*/  EAX ; 
 int /*<<< orphan*/  EBX ; 
 int /*<<< orphan*/  ECX ; 
 int /*<<< orphan*/  ESP ; 
 scalar_t__ alignedsource ; 
 int /*<<< orphan*/  assem_debug (char*,scalar_t__) ; 
 scalar_t__ copy ; 
 int /*<<< orphan*/  emit_addimm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_movimm (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_pushimm (scalar_t__) ; 
 int* instr_addr ; 
 int /*<<< orphan*/  load_regs_entry (int) ; 
 scalar_t__ out ; 
 scalar_t__ slave ; 
 int slen ; 
 scalar_t__ source ; 
 scalar_t__ start ; 
 int /*<<< orphan*/  verify_code ; 

int do_dirty_stub(int i)
{
  assem_debug("do_dirty_stub %x\n",start+i*2);
  u32 alignedlen=((((u32)source)+slen*2+2)&~2)-(u32)alignedsource;
  emit_pushimm(start+i*2+slave);
  emit_movimm(((u32)source)&~3,EAX); //alignedsource
  emit_movimm((u32)copy,EBX);
  emit_movimm((((u32)source+slen*2+2)&~3)-((u32)source&~3),ECX);
  emit_call((int)&verify_code);
  emit_addimm(ESP,4,ESP);
  int entry=(int)out;
  load_regs_entry(i);
  if(entry==(int)out) entry=instr_addr[i];
  emit_jmp(instr_addr[i]);
  return entry;
}
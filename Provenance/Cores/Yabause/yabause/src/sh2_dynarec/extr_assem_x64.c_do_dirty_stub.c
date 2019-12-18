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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int EAX ; 
 int EBX ; 
 int ECX ; 
 scalar_t__ alignedsource ; 
 int /*<<< orphan*/  assem_debug (char*,int) ; 
 scalar_t__ copy ; 
 int /*<<< orphan*/  emit_call (int) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_movimm (int,int) ; 
 int /*<<< orphan*/  emit_movimm64 (int,int) ; 
 int* instr_addr ; 
 int /*<<< orphan*/  load_regs_entry (int) ; 
 scalar_t__ out ; 
 int slave ; 
 int slen ; 
 scalar_t__ source ; 
 int start ; 
 int /*<<< orphan*/  verify_code ; 

int do_dirty_stub(int i)
{
  assem_debug("do_dirty_stub %x\n",start+i*2);
  u32 alignedlen=((((u32)source)+slen*2+2)&~2)-(u32)alignedsource;
  if((u64)source<=0xFFFFFFFF)
    emit_movimm(((u32)source)&~3,EAX); //alignedsource
  else
    emit_movimm64(((u64)source)&~3,EAX); //alignedsource
  emit_movimm((u32)copy,EBX);
  emit_movimm((((u32)source+slen*2+2)&~3)-((u32)source&~3),ECX);
  emit_movimm(start+i*2+slave,12);
  emit_call((int)&verify_code);
  int entry=(int)out;
  load_regs_entry(i);
  if(entry==(int)out) entry=instr_addr[i];
  emit_jmp(instr_addr[i]);
  return entry;
}
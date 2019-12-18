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
typedef  int u8 ;
typedef  int pointer ;

/* Variables and functions */
 int /*<<< orphan*/  Count ; 
 int /*<<< orphan*/  ECX ; 
 int /*<<< orphan*/  HOST_CCREG ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dyna_linker ; 
 int /*<<< orphan*/  emit_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jmp (int) ; 
 int /*<<< orphan*/  emit_loadlp (int,int) ; 
 int /*<<< orphan*/  emit_readword (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_writeword (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  last_count ; 
 int /*<<< orphan*/  next_interupt ; 

emit_extjump(pointer addr, int target)
{
  u8 *ptr=(u8 *)addr;
  assert((ptr[3]&0x0e)==0xa);
  emit_loadlp(target,0);
  emit_loadlp(addr,1);
  //assert(addr>=0x7000000&&addr<0x7FFFFFF);
//DEBUG >
#ifdef DEBUG_CYCLE_COUNT
  emit_readword((int)&last_count,ECX);
  emit_add(HOST_CCREG,ECX,HOST_CCREG);
  emit_readword((int)&next_interupt,ECX);
  emit_writeword(HOST_CCREG,(int)&Count);
  emit_sub(HOST_CCREG,ECX,HOST_CCREG);
  emit_writeword(ECX,(int)&last_count);
#endif
//DEBUG <
  emit_jmp((pointer)dyna_linker);
}
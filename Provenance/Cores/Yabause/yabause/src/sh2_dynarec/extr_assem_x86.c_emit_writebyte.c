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
 int EAX ; 
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_xchg (int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ ** regname ; 

void emit_writebyte(int rt, int addr)
{
  if(rt<4) {
    assem_debug("movb %%%cl,%x\n",regname[rt][1],addr);
    output_byte(0x88);
    output_modrm(0,5,rt);
    output_w32(addr);
  }
  else
  {
    emit_xchg(EAX,rt);
    emit_writebyte(EAX,addr);
    emit_xchg(EAX,rt);
  }
}
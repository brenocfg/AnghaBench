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
 unsigned int EBP ; 
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movss_load(unsigned int addr,unsigned int ssereg)
{
  assem_debug("movss (%%%s),xmm%d\n",regname[addr],ssereg);
  assert(ssereg<8);
  output_byte(0xf3);
  output_byte(0x0f);
  output_byte(0x10);
  if(addr!=EBP) output_modrm(0,addr,ssereg);
  else {output_modrm(1,EBP,ssereg);output_byte(0);}
}
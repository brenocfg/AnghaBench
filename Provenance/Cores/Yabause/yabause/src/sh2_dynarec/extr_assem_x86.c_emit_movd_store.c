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
 int /*<<< orphan*/  assem_debug (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movd_store(unsigned int ssereg,unsigned int addr)
{
  assem_debug("movd xmm%d,(%%%s)\n",ssereg,regname[addr]);
  assert(ssereg<8);
  output_byte(0x66);
  output_byte(0x0f);
  output_byte(0x7e);
  if(addr!=EBP) output_modrm(0,addr,ssereg);
  else {output_modrm(1,EBP,ssereg);output_byte(0);}
}
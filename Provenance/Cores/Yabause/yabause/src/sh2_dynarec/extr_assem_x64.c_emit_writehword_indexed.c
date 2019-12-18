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
 int /*<<< orphan*/  assem_debug (char*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 scalar_t__* regname ; 

void emit_writehword_indexed(int rt, int addr, int rs)
{
  assem_debug("movw %%%s,%x+%%%s\n",regname[rt]+1,addr,regname[rs]);
  output_byte(0x66);
  output_byte(0x89);
  if(addr<128&&addr>=-128) {
    output_modrm(1,rs,rt);
    output_byte(addr);
  }
  else
  {
    output_modrm(2,rs,rt);
    output_w32(addr);
  }
}
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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  assem_debug (char*,...) ; 
 int /*<<< orphan*/  const_one ; 
 int /*<<< orphan*/  const_zero ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_cmovl(u32 *addr,int rt)
{
  assem_debug("cmovl %x,%%%s",(int)addr,regname[rt]);
  if(addr==&const_zero) assem_debug(" [zero]\n");
  else if(addr==&const_one) assem_debug(" [one]\n");
  else assem_debug("\n");
  output_byte(0x0F);
  output_byte(0x4C);
  output_modrm(0,5,rt);
  output_w32((int)addr-(int)out-4); // Note: rip-relative in 64-bit mode
}
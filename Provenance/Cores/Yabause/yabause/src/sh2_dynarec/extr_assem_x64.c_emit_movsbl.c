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

/* Variables and functions */
 int EBP ; 
 int /*<<< orphan*/  assem_debug (char*,int,int) ; 
 int /*<<< orphan*/  emit_movimm64 (int,int) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int* regname ; 

void emit_movsbl(u64 addr, int rt)
{
  if(addr-(u64)out+0x7FFFFFF9>0xFFFFFFFE) {
    emit_movimm64(addr,rt);
    assem_debug("movsbl (%%%s),%%%s\n",regname[rt],regname[rt]);
    output_byte(0x0F);
    output_byte(0xBE);
    if(rt!=EBP) {
      output_modrm(0,rt,rt);
    } else {
      output_modrm(1,rt,rt);
      output_byte(0);
    }
  }
  else
  {
    assem_debug("movsbl %x,%%%s\n",addr,regname[rt]);
    output_byte(0x0F);
    output_byte(0xBE);
    output_modrm(0,5,rt);
    output_w32(addr-(int)out-4); // rip-relative
  }
}
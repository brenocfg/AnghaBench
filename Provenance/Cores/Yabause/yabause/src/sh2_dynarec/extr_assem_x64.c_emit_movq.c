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
 int /*<<< orphan*/  assem_debug (char*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_movimm64 (int,int) ; 
 scalar_t__ out ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_rex (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int* regname ; 

void emit_movq(u64 addr, int rt)
{
  if(addr-(u64)out+0x7FFFFFFA>0xFFFFFFFF) {
    assert(addr-(u64)out+0x7FFFFFFA<0x100000000);
    //TODO: special eax case
    emit_movimm64(addr,rt);
    //FIXME
    assem_debug("mov (%%%s),%%%s\n",regname[rt],regname[rt]);
    output_byte(0x8B);
    output_modrm(0,rt,rt);
    output_byte(0xCC);//remove
  }
  else
  {
    assem_debug("movq %llx,%%%s\n",addr,regname[rt]);
    output_rex(1,0,0,rt>>8);
    output_byte(0x8B);
    output_modrm(0,5,rt);
    output_w32(addr-(int)out-4); // Note: rip-relative in 64-bit mode
  }
}
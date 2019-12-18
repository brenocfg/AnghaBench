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
 int EBP ; 
 int ESP ; 
 int /*<<< orphan*/  assem_debug (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_movswl_indexed (int,int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_sib (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movswl_indexed_map(int addr, int rs, int map, int rt)
{
  assert(map>=0);
  if(map<0) emit_movswl_indexed(addr, rs, rt);
  else {
    assem_debug("movswl %x(%%%s,%%%s,4),%%%s\n",addr,regname[rs],regname[map],regname[rt]);
    assert(rs!=ESP);
    output_byte(0x0F);
    output_byte(0xBF);
    if(addr==0&&rs!=EBP) {
      output_modrm(0,4,rt);
      output_sib(2,map,rs);
    }
    else if(addr<128&&addr>=-128) {
      output_modrm(1,4,rt);
      output_sib(2,map,rs);
      output_byte(addr);
    }
    else
    {
      output_modrm(2,4,rt);
      output_sib(2,map,rs);
      output_w32(addr);
    }
  }
}
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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_writeword_indexed (int,int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_sib (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_writeword_indexed_map(int rt, int addr, int rs, int map, int temp)
{
  if(map<0) emit_writeword_indexed(rt, addr, rs);
  else {
    assem_debug("mov %%%s,%x(%%%s,%%%s,1)\n",regname[rt],addr,regname[rs],regname[map]);
    assert(rs!=ESP);
    output_byte(0x89);
    if(addr==0&&rs!=EBP) {
      output_modrm(0,4,rt);
      output_sib(0,map,rs);
    }
    else if(addr<128&&addr>=-128) {
      output_modrm(1,4,rt);
      output_sib(0,map,rs);
      output_byte(addr);
    }
    else
    {
      output_modrm(2,4,rt);
      output_sib(0,map,rs);
      output_w32(addr);
    }
  }
}
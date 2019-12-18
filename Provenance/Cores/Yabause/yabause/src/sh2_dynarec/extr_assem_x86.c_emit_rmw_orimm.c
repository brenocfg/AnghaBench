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
 int /*<<< orphan*/  assem_debug (char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_sib (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_rmw_orimm(int addr, int map, int imm)
{
  if(map<0) {
    assem_debug("orb $0x%x,(%%%s)\n",imm,regname[addr]);
    assert(addr!=ESP);
    output_byte(0x80);
    output_modrm(0,addr,1);
  }
  else
  {
    assem_debug("orb $0x%x,(%%%s,%%%s,1)\n",imm,regname[addr],regname[map]);
    assert(addr!=ESP);
    output_byte(0x80);
    output_modrm(0,4,1);
    if(addr!=EBP) {
      output_sib(0,map,addr);
    }
    else {
      assert(addr!=map);
      output_sib(0,addr,map);
    }
  }
  output_byte(imm);
}
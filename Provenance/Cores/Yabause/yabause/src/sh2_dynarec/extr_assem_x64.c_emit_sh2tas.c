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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_adc (int,int) ; 
 int /*<<< orphan*/  emit_rmw_orimm (int,int,int) ; 
 int /*<<< orphan*/  emit_shrimm (int,int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_sib (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_sh2tas(int addr, int map, int sr)
{
  emit_shrimm(sr,1,sr);
  if(map<0) {
    assem_debug("cmpb $1,(%%%s)\n",regname[addr]);
    assert(addr!=ESP);
    output_byte(0x80);
    output_modrm(0,addr,7);
  }
  else
  {
    assem_debug("cmpb $1,(%%%s,%%%s,1)\n",regname[addr],regname[map]);
    assert(addr!=ESP);
    output_byte(0x80);
    output_modrm(0,4,7);
    if(addr!=EBP) {
      output_sib(0,map,addr);
    }
    else {
      assert(addr!=map);
      output_sib(0,addr,map);
    }
  }
  output_byte(1);
  emit_adc(sr,sr);
  emit_rmw_orimm(addr,map,0x80);
}
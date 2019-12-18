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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_movswl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_sib (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movswl_map(u64 addr, int map, int rt)
{
  if(map<0) emit_movswl(addr, rt);
  else
  {
    //FIXME
    assem_debug("addr32 movswl %x(,%%%s,4),%%%s\n",addr,regname[map],regname[rt]);
    output_byte(0x67);
    output_byte(0x0F);
    output_byte(0xBF);
    output_modrm(0,4,rt);
    output_sib(2,map,5);
    output_w32(addr);
  }
}
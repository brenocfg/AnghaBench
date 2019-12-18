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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_shl(unsigned int rs,unsigned int shift,unsigned int rt)
{
  assert(rs<16);
  assert(rt<16);
  assert(shift<16);
  //if(imm==1) ...
  assem_debug("lsl %s,%s,%s\n",regname[rt],regname[rs],regname[shift]);
  output_w32(0xe1a00000|rd_rn_rm(rt,0,rs)|0x10|(shift<<8));
}
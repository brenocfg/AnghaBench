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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  FP ; 
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dynarec_local ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movsbl(int addr, int rt)
{
  u32 offset = addr-(u32)&dynarec_local;
  assert(offset<256);
  assem_debug("ldrsb %s,fp+%d\n",regname[rt],offset);
  output_w32(0xe1d000d0|rd_rn_rm(rt,FP,0)|((offset<<4)&0xf00)|(offset&0xf));
}
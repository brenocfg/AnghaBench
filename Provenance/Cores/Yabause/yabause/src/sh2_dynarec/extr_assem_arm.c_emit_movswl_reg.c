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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_sarimm (int,int,int) ; 
 int /*<<< orphan*/  emit_shlimm (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movswl_reg(int rs, int rt)
{
  #ifdef HAVE_ARMv6
  assem_debug("sxth %s,%s\n",regname[rt],regname[rs]);
  output_w32(0xe6bf0070|rd_rn_rm(rt,0,rs));
  #else
  emit_shlimm(rs,16,rt);
  emit_sarimm(rt,16,rt);
  #endif
}
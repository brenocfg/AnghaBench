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
 int /*<<< orphan*/  HOST_TEMPREG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_cmovl_imm (int,int) ; 
 int /*<<< orphan*/  emit_cmp (int,int) ; 
 int /*<<< orphan*/  emit_movimm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_sbcs (int,int,int /*<<< orphan*/ ) ; 

void emit_set_if_less64_32(int u1, int l1, int u2, int l2, int rt)
{
  //assem_debug("set if less64 (%%%s,%%%s,%%%s,%%%s),%%%s\n",regname[u1],regname[l1],regname[u2],regname[l2],regname[rt]);
  assert(u1!=rt);
  assert(u2!=rt);
  emit_cmp(l1,l2);
  emit_movimm(0,rt);
  emit_sbcs(u1,u2,HOST_TEMPREG);
  emit_cmovl_imm(1,rt);
}
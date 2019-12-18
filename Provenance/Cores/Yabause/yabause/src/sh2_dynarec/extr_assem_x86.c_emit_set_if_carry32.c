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
 int /*<<< orphan*/  emit_adcimm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_cmp (int,int) ; 
 int /*<<< orphan*/  emit_movimm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_zeroreg (int) ; 

void emit_set_if_carry32(int rs1, int rs2, int rt)
{
  //assem_debug("set if carry (%%%s,%%%s),%%%s\n",regname[rs1],regname[rs2],regname[rt]);
  if(rs1!=rt&&rs2!=rt) emit_zeroreg(rt);
  emit_cmp(rs1,rs2);
  if(rs1==rt||rs2==rt) emit_movimm(0,rt);
  emit_adcimm(0,rt);
}
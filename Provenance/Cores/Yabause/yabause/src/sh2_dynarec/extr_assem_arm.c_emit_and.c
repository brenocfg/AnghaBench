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
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_and(unsigned int rs1,unsigned int rs2,unsigned int rt)
{
  assem_debug("and %s,%s,%s\n",regname[rt],regname[rs1],regname[rs2]);
  output_w32(0xe0000000|rd_rn_rm(rt,rs1,rs2));
}
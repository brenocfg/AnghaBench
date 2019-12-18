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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_smull(unsigned int rs1, unsigned int rs2, unsigned int hi, unsigned int lo)
{
  assem_debug("smull %s, %s, %s, %s\n",regname[lo],regname[hi],regname[rs1],regname[rs2]);
  assert(rs1<16);
  assert(rs2<16);
  assert(hi<16);
  assert(lo<16);
  assert(hi!=rs1&&hi!=rs2);
  assert(lo!=rs1&&lo!=rs2);
  output_w32(0xe0c00090|(hi<<16)|(lo<<12)|(rs2<<8)|rs1);
}
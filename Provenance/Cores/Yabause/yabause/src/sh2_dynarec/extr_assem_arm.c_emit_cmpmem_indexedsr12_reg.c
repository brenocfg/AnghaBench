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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_cmpimm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_cmpmem_indexedsr12_reg(int base,int r,int imm)
{
  assert(imm<128&&imm>=0);
  assert(r>=0&&r<16);
  assem_debug("ldrb lr,%s,%s lsr #12\n",regname[base],regname[r]);
  output_w32(0xe7d00000|rd_rn_rm(HOST_TEMPREG,base,r)|0x620);
  emit_cmpimm(HOST_TEMPREG,imm);
}
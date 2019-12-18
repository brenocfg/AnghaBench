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
 int /*<<< orphan*/  emit_mov (unsigned int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_multiply(unsigned int rs1,unsigned int rs2,unsigned int rt)
{
  if(rs1==rt&&rs2==rt) {emit_mov(rs1,14);emit_multiply(14,14,rt);}
  else if(rs1==rt) {emit_multiply(rs2,rs1,rt);}
  else {
    assem_debug("mul %s, %s, %s\n",regname[rt],regname[rs1],regname[rs2]);
    assert(rs1<16);
    assert(rs2<16);
    assert(rt<16);
    output_w32(0xe0000090|(rt<<16)|(rs2<<8)|rs1);
  }
}
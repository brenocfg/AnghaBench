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
 int /*<<< orphan*/  assem_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_rex (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  output_w64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regname ; 

void emit_movimm64(u64 imm,unsigned int rt)
{
  assem_debug("movq $0x%llx,%%%s\n",imm,regname[rt]);
  assert(rt<16);
  output_rex(1,0,0,rt>>3);
  output_byte(0xB8+(rt&7));
  output_w64(imm);
}
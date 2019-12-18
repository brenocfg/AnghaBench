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
 int /*<<< orphan*/  assem_debug (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_addimm_no_flags(int imm,int rt)
{
  if(imm!=0) {
    assem_debug("lea %d(%%%s),%%%s\n",imm,regname[rt],regname[rt]);
    output_byte(0x8D);
    if(imm<128&&imm>=-128) {
      output_modrm(1,rt,rt);
      output_byte(imm);
    }else{
      output_modrm(2,rt,rt);
      output_w32(imm);
    }
  }
}
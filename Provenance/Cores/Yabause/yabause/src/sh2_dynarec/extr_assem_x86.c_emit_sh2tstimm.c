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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_cmovne_reg (int,int) ; 
 int /*<<< orphan*/  emit_orimm (int,int,int) ; 
 int /*<<< orphan*/  emit_testimm (int,int) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_sh2tstimm(int s, int imm, int sr, int temp)
{
  assert(temp>=0);
  emit_orimm(sr,1,sr);
  emit_testimm(s,imm);
  //emit_addimm(sr,-1,temp);
  assem_debug("lea -1(%%%s),%%%s\n",regname[sr],regname[temp]);
  output_byte(0x8D);
  output_modrm(1,sr,temp);
  output_byte(0xFF);
  emit_cmovne_reg(temp,sr);
}
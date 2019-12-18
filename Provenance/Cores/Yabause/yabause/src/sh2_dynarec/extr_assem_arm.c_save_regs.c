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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  assem_debug (char*) ; 
 int /*<<< orphan*/  output_w32 (int) ; 

void save_regs(u32 reglist)
{
  reglist&=0x100f; // only save the caller-save registers, r0-r3, r12
  if(!reglist) return;
  assem_debug("stmia fp,{");
  if(reglist&1) assem_debug("r0, ");
  if(reglist&2) assem_debug("r1, ");
  if(reglist&4) assem_debug("r2, ");
  if(reglist&8) assem_debug("r3, ");
  if(reglist&0x1000) assem_debug("r12");
  assem_debug("}\n");
  output_w32(0xe88b0000|reglist);
}
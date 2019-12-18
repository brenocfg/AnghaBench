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
 int /*<<< orphan*/  assem_debug (char*,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int rd_rn_rm (int,int,int /*<<< orphan*/ ) ; 

void emit_jno_unlikely(int a)
{
  //emit_jno(a);
  assem_debug("addvc pc,pc,#? (%x)\n",/*a-(int)out-8,*/a);
  output_w32(0x72800000|rd_rn_rm(15,15,0));
}
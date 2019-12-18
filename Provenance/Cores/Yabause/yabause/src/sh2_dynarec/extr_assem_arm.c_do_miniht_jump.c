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
 int /*<<< orphan*/  emit_cmp (int,int) ; 
 int /*<<< orphan*/  emit_jmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_ldreq_indexed (int,int,int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/ ** jump_vaddr_reg ; 
 size_t slave ; 

void do_miniht_jump(int rs,int rh,int ht) {
  emit_cmp(rh,rs);
  emit_ldreq_indexed(ht,4,15);
  #ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
  emit_mov(rs,7);
  emit_jmp(jump_vaddr_reg[slave][7]);
  #else
  emit_jmp(jump_vaddr_reg[slave][rs]);
  #endif
}
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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  emit_cmpmem_indexed (scalar_t__,int,int) ; 
 int /*<<< orphan*/  emit_jmpreg (int) ; 
 int /*<<< orphan*/  emit_jne (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_readword_indexed (scalar_t__,int,int) ; 
 int /*<<< orphan*/ ** jump_vaddr_reg ; 
 scalar_t__ mini_ht_master ; 
 scalar_t__ mini_ht_slave ; 
 int slave ; 

void do_miniht_jump(int rs,int rh,int ht) {
  emit_cmpmem_indexed(slave?(u32)mini_ht_slave:(u32)mini_ht_master,rh,rs);
  emit_jne(jump_vaddr_reg[slave][rs]);
  emit_readword_indexed(slave?(u32)mini_ht_slave+4:(u32)mini_ht_master+4,rh,rh);
  emit_jmpreg(rh);
}
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
 int /*<<< orphan*/  delete_trivially_dead_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcse_after_reload_main (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int /*<<< orphan*/  rebuild_jump_labels (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_gcse2 (void)
{
  gcse_after_reload_main (get_insns ());
  rebuild_jump_labels (get_insns ());
  delete_trivially_dead_insns (get_insns (), max_reg_num ());
  return 0;
}
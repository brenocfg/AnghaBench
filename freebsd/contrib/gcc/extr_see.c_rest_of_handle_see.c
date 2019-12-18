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
 int /*<<< orphan*/  CLEANUP_EXPENSIVE ; 
 int /*<<< orphan*/  PROP_DEATH_NOTES ; 
 int /*<<< orphan*/  UPDATE_LIFE_GLOBAL_RM_NOTES ; 
 int /*<<< orphan*/  cleanup_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_trivially_dead_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  max_reg_num () ; 
 int no_new_pseudos ; 
 int /*<<< orphan*/  reg_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  see_main () ; 
 int /*<<< orphan*/  update_life_info_in_dirty_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_see (void)
{
  int no_new_pseudos_bcp = no_new_pseudos;

  no_new_pseudos = 0;
  see_main ();
  no_new_pseudos = no_new_pseudos_bcp;
  
  delete_trivially_dead_insns (get_insns (), max_reg_num ());
  update_life_info_in_dirty_blocks (UPDATE_LIFE_GLOBAL_RM_NOTES, 
  				    (PROP_DEATH_NOTES));
  cleanup_cfg (CLEANUP_EXPENSIVE);
  reg_scan (get_insns (), max_reg_num ());

  return 0;
}
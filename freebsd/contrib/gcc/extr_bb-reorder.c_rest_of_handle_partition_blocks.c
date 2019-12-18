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
 int PROP_DEATH_NOTES ; 
 int PROP_LOG_LINKS ; 
 int PROP_REG_INFO ; 
 int /*<<< orphan*/  UPDATE_LIFE_GLOBAL_RM_NOTES ; 
 int /*<<< orphan*/  allocate_reg_life_data () ; 
 int no_new_pseudos ; 
 int /*<<< orphan*/  partition_hot_cold_basic_blocks () ; 
 int /*<<< orphan*/  update_life_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
rest_of_handle_partition_blocks (void)
{
  no_new_pseudos = 0;
  partition_hot_cold_basic_blocks ();
  allocate_reg_life_data ();
  update_life_info (NULL, UPDATE_LIFE_GLOBAL_RM_NOTES,
		    PROP_LOG_LINKS | PROP_REG_INFO | PROP_DEATH_NOTES);
  no_new_pseudos = 1;
  return 0;
}
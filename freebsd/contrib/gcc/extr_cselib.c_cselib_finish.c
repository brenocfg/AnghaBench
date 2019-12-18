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
 int /*<<< orphan*/  cselib_clear_table () ; 
 scalar_t__ cselib_hash_table ; 
 int /*<<< orphan*/  cselib_val_pool ; 
 int /*<<< orphan*/  elt_list_pool ; 
 int /*<<< orphan*/  elt_loc_list_pool ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  free_alloc_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_delete (scalar_t__) ; 
 scalar_t__ n_useless_values ; 
 scalar_t__ next_unknown_value ; 
 scalar_t__ used_regs ; 
 int /*<<< orphan*/  value_pool ; 

void
cselib_finish (void)
{
  free_alloc_pool (elt_list_pool);
  free_alloc_pool (elt_loc_list_pool);
  free_alloc_pool (cselib_val_pool);
  free_alloc_pool (value_pool);
  cselib_clear_table ();
  htab_delete (cselib_hash_table);
  free (used_regs);
  used_regs = 0;
  cselib_hash_table = 0;
  n_useless_values = 0;
  next_unknown_value = 0;
}
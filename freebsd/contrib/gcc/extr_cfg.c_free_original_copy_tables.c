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
 int /*<<< orphan*/ * bb_copy ; 
 int /*<<< orphan*/ * bb_original ; 
 int /*<<< orphan*/  free_alloc_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * original_copy_bb_pool ; 

void
free_original_copy_tables (void)
{
  gcc_assert (original_copy_bb_pool);
  htab_delete (bb_copy);
  htab_delete (bb_original);
  free_alloc_pool (original_copy_bb_pool);
  bb_copy = NULL;
  bb_original = NULL;
  original_copy_bb_pool = NULL;
}
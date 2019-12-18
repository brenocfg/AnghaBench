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
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocks_with_calls ; 
 int /*<<< orphan*/  cuid_insn ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_modify_mem_tables () ; 
 int /*<<< orphan*/  modify_mem_list_set ; 
 int /*<<< orphan*/  reg_set_bitmap ; 
 int /*<<< orphan*/  reg_set_in_block ; 
 int /*<<< orphan*/  sbitmap_vector_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_cuid ; 

__attribute__((used)) static void
free_gcse_mem (void)
{
  free (uid_cuid);
  free (cuid_insn);

  BITMAP_FREE (reg_set_bitmap);

  sbitmap_vector_free (reg_set_in_block);
  free_modify_mem_tables ();
  BITMAP_FREE (modify_mem_list_set);
  BITMAP_FREE (blocks_with_calls);
}
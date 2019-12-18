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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/ * BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/ * names_to_release ; 
 int /*<<< orphan*/  need_to_initialize_update_ssa_p ; 

void
release_ssa_name_after_update_ssa (tree name)
{
  gcc_assert (!need_to_initialize_update_ssa_p);

  if (names_to_release == NULL)
    names_to_release = BITMAP_ALLOC (NULL);

  bitmap_set_bit (names_to_release, SSA_NAME_VERSION (name));
}
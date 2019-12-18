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
 int /*<<< orphan*/  add_new_name_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_update_ssa () ; 
 scalar_t__ need_to_initialize_update_ssa_p ; 

void
register_new_name_mapping (tree new, tree old)
{
  if (need_to_initialize_update_ssa_p)
    init_update_ssa ();

  add_new_name_mapping (new, old);
}
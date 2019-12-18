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
 int /*<<< orphan*/  all_ipa_passes ; 
 int /*<<< orphan*/  bitmap_obstack_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_obstack_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cfun ; 
 int /*<<< orphan*/  execute_ipa_pass_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_register_cfg_hooks () ; 

__attribute__((used)) static void
ipa_passes (void)
{
  cfun = NULL;
  tree_register_cfg_hooks ();
  bitmap_obstack_initialize (NULL);
  execute_ipa_pass_list (all_ipa_passes);
  bitmap_obstack_release (NULL);
}
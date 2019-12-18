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
 int /*<<< orphan*/  cleanup_tree_cfg () ; 

__attribute__((used)) static unsigned int
execute_cleanup_cfg_pre_ipa (void)
{
  cleanup_tree_cfg ();
  return 0;
}
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
 int /*<<< orphan*/  pushdecl_top_level_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

tree
pushdecl_top_level_maybe_friend (tree x, bool is_friend)
{
  return pushdecl_top_level_1 (x, NULL, is_friend);
}
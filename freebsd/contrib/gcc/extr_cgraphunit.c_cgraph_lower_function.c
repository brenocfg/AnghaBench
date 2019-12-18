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
struct cgraph_node {int lowered; int /*<<< orphan*/  decl; } ;

/* Variables and functions */
 int /*<<< orphan*/  tree_lowering_passes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cgraph_lower_function (struct cgraph_node *node)
{
  if (node->lowered)
    return;
  tree_lowering_passes (node->decl);
  node->lowered = true;
}
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
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
sync_resolve_return (tree params, tree result)
{
  tree ptype = TREE_TYPE (TREE_TYPE (TREE_VALUE (params)));
  ptype = TYPE_MAIN_VARIANT (ptype);
  return convert (ptype, result);
}
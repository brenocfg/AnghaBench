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
typedef  int /*<<< orphan*/  reshape_iter ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_type_nelts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  reshape_init_array_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
reshape_init_array (tree type, reshape_iter *d)
{
  tree max_index = NULL_TREE;

  gcc_assert (TREE_CODE (type) == ARRAY_TYPE);

  if (TYPE_DOMAIN (type))
    max_index = array_type_nelts (type);

  return reshape_init_array_1 (TREE_TYPE (type), max_index, d);
}
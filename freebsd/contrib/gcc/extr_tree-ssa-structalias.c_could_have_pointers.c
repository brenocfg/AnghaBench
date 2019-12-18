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
 scalar_t__ AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ COMPLEX_TYPE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
could_have_pointers (tree t)
{
  tree type = TREE_TYPE (t);

  if (POINTER_TYPE_P (type)
      || AGGREGATE_TYPE_P (type)
      || TREE_CODE (type) == COMPLEX_TYPE)
    return true;

  return false;
}
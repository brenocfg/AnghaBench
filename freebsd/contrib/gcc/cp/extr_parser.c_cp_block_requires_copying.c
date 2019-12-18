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
 scalar_t__ TYPE_HAS_CONSTRUCTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_NEEDS_CONSTRUCTING (int /*<<< orphan*/ ) ; 
 scalar_t__ block_requires_copying (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cp_block_requires_copying (tree exp)
{
  return (block_requires_copying (exp) 
		|| TYPE_HAS_CONSTRUCTOR (TREE_TYPE (exp))
		|| TYPE_NEEDS_CONSTRUCTING (TREE_TYPE (exp)));
}
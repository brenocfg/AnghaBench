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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ ANON_AGGR_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
count_fields (tree fields)
{
  tree x;
  int n_fields = 0;
  for (x = fields; x; x = TREE_CHAIN (x))
    {
      if (TREE_CODE (x) == FIELD_DECL && ANON_AGGR_TYPE_P (TREE_TYPE (x)))
	n_fields += count_fields (TYPE_FIELDS (TREE_TYPE (x)));
      else
	n_fields += 1;
    }
  return n_fields;
}
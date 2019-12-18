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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ DFmode ; 
 scalar_t__ FIELD_DECL ; 
 unsigned int MAX (unsigned int,int) ; 
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_FIELDS (int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * error_mark_node ; 

unsigned int
rs6000_special_round_type_align (tree type, unsigned int computed,
				 unsigned int specified)
{
  unsigned int align = MAX (computed, specified);
  tree field = TYPE_FIELDS (type);

  /* Skip all non field decls */
  while (field != NULL && TREE_CODE (field) != FIELD_DECL)
    field = TREE_CHAIN (field);

  if (field != NULL && field != type)
    {
      type = TREE_TYPE (field);
      while (TREE_CODE (type) == ARRAY_TYPE)
	type = TREE_TYPE (type);

      if (type != error_mark_node && TYPE_MODE (type) == DFmode)
	align = MAX (align, 64);
    }

  return align;
}
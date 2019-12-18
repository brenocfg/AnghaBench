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
 scalar_t__ FIELD_DECL ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 int /*<<< orphan*/  TARGET_NEWABI ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 

__attribute__((used)) static int
mips_fpr_return_fields (tree valtype, tree *fields)
{
  tree field;
  int i;

  if (!TARGET_NEWABI)
    return 0;

  if (TREE_CODE (valtype) != RECORD_TYPE)
    return 0;

  i = 0;
  for (field = TYPE_FIELDS (valtype); field != 0; field = TREE_CHAIN (field))
    {
      if (TREE_CODE (field) != FIELD_DECL)
	continue;

      if (TREE_CODE (TREE_TYPE (field)) != REAL_TYPE)
	return 0;

      if (i == 2)
	return 0;

      fields[i++] = field;
    }
  return i;
}
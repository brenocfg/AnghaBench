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
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ TYPE_VFIELD (scalar_t__) ; 
 scalar_t__ fields_compatible_p (scalar_t__,scalar_t__) ; 

tree
find_compatible_field (tree record, tree orig_field)
{
  tree f;

  for (f = TYPE_FIELDS (record); f ; f = TREE_CHAIN (f))
    if (TREE_CODE (f) == FIELD_DECL
	&& fields_compatible_p (f, orig_field))
      return f;

  /* ??? Why isn't this on the main fields list?  */
  f = TYPE_VFIELD (record);
  if (f && TREE_CODE (f) == FIELD_DECL
      && fields_compatible_p (f, orig_field))
    return f;

  /* ??? We should abort here, but Java appears to do Bad Things
     with inherited fields.  */
  return orig_field;
}
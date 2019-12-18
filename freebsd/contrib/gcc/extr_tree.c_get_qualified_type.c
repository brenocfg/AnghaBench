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
 scalar_t__ NULL_TREE ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_NEXT_VARIANT (scalar_t__) ; 
 int TYPE_QUALS (scalar_t__) ; 
 scalar_t__ check_qualified_type (scalar_t__,scalar_t__,int) ; 

tree
get_qualified_type (tree type, int type_quals)
{
  tree t;

  if (TYPE_QUALS (type) == type_quals)
    return type;

  /* Search the chain of variants to see if there is already one there just
     like the one we need to have.  If so, use that existing one.  We must
     preserve the TYPE_NAME, since there is code that depends on this.  */
  for (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
    if (check_qualified_type (t, type, type_quals))
      return t;

  return NULL_TREE;
}
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
 scalar_t__ IDENTIFIER_NODE ; 
 scalar_t__ IDENTIFIER_TEMPLATE (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ constructor_name_full (scalar_t__) ; 

bool
constructor_name_p (tree name, tree type)
{
  tree ctor_name;

  if (!name)
    return false;

  if (TREE_CODE (name) != IDENTIFIER_NODE)
    return false;

  ctor_name = constructor_name_full (type);
  if (name == ctor_name)
    return true;
  if (IDENTIFIER_TEMPLATE (ctor_name)
      && name == IDENTIFIER_TEMPLATE (ctor_name))
    return true;
  return false;
}
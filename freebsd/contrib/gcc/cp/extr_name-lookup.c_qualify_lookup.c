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
 int LOOKUP_PREFER_NAMESPACES ; 
 int LOOKUP_PREFER_TYPES ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 

__attribute__((used)) static bool
qualify_lookup (tree val, int flags)
{
  if (val == NULL_TREE)
    return false;
  if ((flags & LOOKUP_PREFER_NAMESPACES) && TREE_CODE (val) == NAMESPACE_DECL)
    return true;
  if ((flags & LOOKUP_PREFER_TYPES)
      && (TREE_CODE (val) == TYPE_DECL || TREE_CODE (val) == TEMPLATE_DECL))
    return true;
  if (flags & (LOOKUP_PREFER_NAMESPACES | LOOKUP_PREFER_TYPES))
    return false;
  return true;
}
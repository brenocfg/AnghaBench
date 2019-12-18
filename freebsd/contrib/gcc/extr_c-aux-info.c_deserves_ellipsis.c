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
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static int
deserves_ellipsis (tree fntype)
{
  tree formal_type;

  formal_type = TYPE_ARG_TYPES (fntype);
  while (formal_type && TREE_VALUE (formal_type) != void_type_node)
    formal_type = TREE_CHAIN (formal_type);

  /* If there were at least some parameters, and if the formals-types-list
     petered out to a NULL (i.e. without being terminated by a void_type_node)
     then we need to tack on an ellipsis.  */

  return (!formal_type && TYPE_ARG_TYPES (fntype));
}
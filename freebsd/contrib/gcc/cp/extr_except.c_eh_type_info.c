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
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ build_java_class_ref (int /*<<< orphan*/ ) ; 
 scalar_t__ decl_is_java_type (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ get_tinfo_decl (scalar_t__) ; 

tree
eh_type_info (tree type)
{
  tree exp;

  if (type == NULL_TREE || type == error_mark_node)
    return type;

  if (decl_is_java_type (type, 0))
    exp = build_java_class_ref (TREE_TYPE (type));
  else
    exp = get_tinfo_decl (type);

  return exp;
}
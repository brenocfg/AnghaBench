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
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 scalar_t__ TYPE_STUB_DECL (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
get_type_decl (tree t)
{
  if (TREE_CODE (t) == TYPE_DECL)
    return t;
  if (TYPE_P (t))
    return TYPE_STUB_DECL (t);
  gcc_assert (t == error_mark_node);
  return t;
}
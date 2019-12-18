#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cgraph_varpool_node {int /*<<< orphan*/  decl; int /*<<< orphan*/  finalized; } ;
typedef  enum availability { ____Placeholder_availability } availability ;
struct TYPE_2__ {int /*<<< orphan*/  (* binds_local_p ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AVAIL_AVAILABLE ; 
 int AVAIL_NOT_AVAILABLE ; 
 int AVAIL_OVERWRITABLE ; 
 int /*<<< orphan*/  DECL_COMDAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_function_flags_ready ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__ targetm ; 

enum availability
cgraph_variable_initializer_availability (struct cgraph_varpool_node *node)
{
  gcc_assert (cgraph_function_flags_ready);
  if (!node->finalized)
    return AVAIL_NOT_AVAILABLE;
  if (!TREE_PUBLIC (node->decl))
    return AVAIL_AVAILABLE;
  /* If the variable can be overwritten, return OVERWRITABLE.  Takes
     care of at least two notable extensions - the COMDAT variables
     used to share template instantiations in C++.  */
  if (!(*targetm.binds_local_p) (node->decl) && !DECL_COMDAT (node->decl))
    return AVAIL_OVERWRITABLE;
  return AVAIL_AVAILABLE;
}
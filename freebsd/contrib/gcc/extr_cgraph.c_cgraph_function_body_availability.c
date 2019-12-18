#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ externally_visible; scalar_t__ local; } ;
struct cgraph_node {int /*<<< orphan*/  decl; TYPE_1__ local; int /*<<< orphan*/  analyzed; } ;
typedef  enum availability { ____Placeholder_availability } availability ;
struct TYPE_4__ {int /*<<< orphan*/  (* binds_local_p ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int AVAIL_AVAILABLE ; 
 int AVAIL_LOCAL ; 
 int AVAIL_NOT_AVAILABLE ; 
 int AVAIL_OVERWRITABLE ; 
 int /*<<< orphan*/  DECL_COMDAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_function_flags_ready ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

enum availability
cgraph_function_body_availability (struct cgraph_node *node)
{
  enum availability avail;
  gcc_assert (cgraph_function_flags_ready);
  if (!node->analyzed)
    avail = AVAIL_NOT_AVAILABLE;
  else if (node->local.local)
    avail = AVAIL_LOCAL;
  else if (node->local.externally_visible)
    avail = AVAIL_AVAILABLE;

  /* If the function can be overwritten, return OVERWRITABLE.  Take
     care at least of two notable extensions - the COMDAT functions
     used to share template instantiations in C++ (this is symmetric
     to code cp_cannot_inline_tree_fn and probably shall be shared and
     the inlinability hooks completely eliminated).

     ??? Does the C++ one definition rule allow us to always return
     AVAIL_AVAILABLE here?  That would be good reason to preserve this
     hook Similarly deal with extern inline functions - this is again
     necessary to get C++ shared functions having keyed templates
     right and in the C extension documentation we probably should
     document the requirement of both versions of function (extern
     inline and offline) having same side effect characteristics as
     good optimization is what this optimization is about.  */

  else if (!(*targetm.binds_local_p) (node->decl)
	   && !DECL_COMDAT (node->decl) && !DECL_EXTERNAL (node->decl))
    avail = AVAIL_OVERWRITABLE;
  else avail = AVAIL_AVAILABLE;

  return avail;
}
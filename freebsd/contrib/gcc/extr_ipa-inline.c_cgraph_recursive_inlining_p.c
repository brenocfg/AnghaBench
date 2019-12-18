#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ disregard_inline_limits; } ;
struct TYPE_6__ {TYPE_2__* inlined_to; } ;
struct cgraph_node {scalar_t__ decl; TYPE_1__ local; TYPE_3__ global; } ;
struct TYPE_5__ {scalar_t__ decl; } ;

/* Variables and functions */
 char* N_ (char*) ; 

__attribute__((used)) static bool
cgraph_recursive_inlining_p (struct cgraph_node *to,
			     struct cgraph_node *what,
			     const char **reason)
{
  bool recursive;
  if (to->global.inlined_to)
    recursive = what->decl == to->global.inlined_to->decl;
  else
    recursive = what->decl == to->decl;
  /* Marking recursive function inline has sane semantic and thus we should
     not warn on it.  */
  if (recursive && reason)
    *reason = (what->local.disregard_inline_limits
	       ? N_("recursive inlining") : "");
  return recursive;
}
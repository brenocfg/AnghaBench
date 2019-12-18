#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* edge ;
typedef  scalar_t__ basic_block ;
struct TYPE_7__ {scalar_t__ dest; TYPE_1__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_DIRTY ; 
 scalar_t__ force_nonfallthru_and_redirect (TYPE_2__*,scalar_t__) ; 
 scalar_t__ redirect_edge_and_branch (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static basic_block
rtl_redirect_edge_and_branch_force (edge e, basic_block target)
{
  if (redirect_edge_and_branch (e, target)
      || e->dest == target)
    return NULL;

  /* In case the edge redirection failed, try to force it to be non-fallthru
     and redirect newly created simplejump.  */
  e->src->flags |= BB_DIRTY;
  return force_nonfallthru_and_redirect (e, target);
}
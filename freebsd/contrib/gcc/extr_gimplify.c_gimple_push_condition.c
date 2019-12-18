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
struct TYPE_2__ {scalar_t__ conditions; int /*<<< orphan*/  conditional_cleanups; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* gimplify_ctxp ; 

__attribute__((used)) static void
gimple_push_condition (void)
{
#ifdef ENABLE_CHECKING
  if (gimplify_ctxp->conditions == 0)
    gcc_assert (!gimplify_ctxp->conditional_cleanups);
#endif
  ++(gimplify_ctxp->conditions);
}
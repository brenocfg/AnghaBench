#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  branches_taken; int /*<<< orphan*/  branches_executed; int /*<<< orphan*/  branches; int /*<<< orphan*/  calls_executed; int /*<<< orphan*/  calls; } ;
typedef  TYPE_2__ coverage_t ;
struct TYPE_8__ {scalar_t__ count; TYPE_1__* src; int /*<<< orphan*/  is_unconditional; scalar_t__ is_call_non_return; } ;
typedef  TYPE_3__ arc_t ;
struct TYPE_6__ {scalar_t__ count; } ;

/* Variables and functions */

__attribute__((used)) static void
add_branch_counts (coverage_t *coverage, const arc_t *arc)
{
  if (arc->is_call_non_return)
    {
      coverage->calls++;
      if (arc->src->count)
	coverage->calls_executed++;
    }
  else if (!arc->is_unconditional)
    {
      coverage->branches++;
      if (arc->src->count)
	coverage->branches_executed++;
      if (arc->count)
	coverage->branches_taken++;
    }
}
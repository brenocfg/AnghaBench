#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* src; scalar_t__ count; TYPE_1__* dst; scalar_t__ fall_through; int /*<<< orphan*/  is_unconditional; scalar_t__ is_call_non_return; } ;
typedef  TYPE_3__ arc_t ;
struct TYPE_6__ {scalar_t__ count; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_call_return; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  flag_counts ; 
 scalar_t__ flag_unconditional ; 
 int /*<<< orphan*/  fnotice (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  format_gcov (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
output_branch_count (FILE *gcov_file, int ix, const arc_t *arc)
{

  if (arc->is_call_non_return)
    {
      if (arc->src->count)
	{
	  fnotice (gcov_file, "call   %2d returned %s\n", ix,
		   format_gcov (arc->src->count - arc->count,
				arc->src->count, -flag_counts));
	}
      else
	fnotice (gcov_file, "call   %2d never executed\n", ix);
    }
  else if (!arc->is_unconditional)
    {
      if (arc->src->count)
	fnotice (gcov_file, "branch %2d taken %s%s\n", ix,
		 format_gcov (arc->count, arc->src->count, -flag_counts),
		 arc->fall_through ? " (fallthrough)" : "");
      else
	fnotice (gcov_file, "branch %2d never executed\n", ix);
    }
  else if (flag_unconditional && !arc->dst->is_call_return)
    {
      if (arc->src->count)
	fnotice (gcov_file, "unconditional %2d taken %s\n", ix,
		 format_gcov (arc->count, arc->src->count, -flag_counts));
      else
	fnotice (gcov_file, "unconditional %2d never executed\n", ix);
    }
  else
    return 0;
  return 1;

}
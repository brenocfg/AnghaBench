#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int in_directive; scalar_t__ save_comments; } ;
struct TYPE_9__ {TYPE_3__* line_table; int /*<<< orphan*/  directive_line; TYPE_2__ directive_result; TYPE_1__ state; } ;
typedef  TYPE_4__ cpp_reader ;
struct TYPE_8__ {int /*<<< orphan*/  highest_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_PADDING ; 

__attribute__((used)) static void
start_directive (cpp_reader *pfile)
{
  /* Setup in-directive state.  */
  pfile->state.in_directive = 1;
  pfile->state.save_comments = 0;
  pfile->directive_result.type = CPP_PADDING;

  /* Some handlers need the position of the # for diagnostics.  */
  pfile->directive_line = pfile->line_table->highest_line;
}
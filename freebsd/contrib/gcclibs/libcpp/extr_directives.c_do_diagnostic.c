#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  prevent_expansion; int /*<<< orphan*/  in_diagnostic; } ;
struct TYPE_11__ {TYPE_1__ state; TYPE_3__* directive; TYPE_2__* cur_token; } ;
typedef  TYPE_4__ cpp_reader ;
struct TYPE_10__ {char* name; } ;
struct TYPE_9__ {int /*<<< orphan*/  src_loc; } ;

/* Variables and functions */
 scalar_t__ _cpp_begin_message (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_output_line (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
do_diagnostic (cpp_reader *pfile, int code, int print_dir)
{
  if (_cpp_begin_message (pfile, code, pfile->cur_token[-1].src_loc, 0))
    {
      if (print_dir)
	fprintf (stderr, "#%s ", pfile->directive->name);
      pfile->state.prevent_expansion++;
      /* APPLE LOCAL #error with unmatched quotes 5607574 */
      pfile->state.in_diagnostic++;
      cpp_output_line (pfile, stderr);
      /* APPLE LOCAL #error with unmatched quotes 5607574 */
      pfile->state.in_diagnostic--;
      pfile->state.prevent_expansion--;
    }
}
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
struct dump_file_info {int flags; } ;
typedef  enum tree_dump_index { ____Placeholder_tree_dump_index } tree_dump_index ;
struct TYPE_4__ {int /*<<< orphan*/  static_pass_number; } ;
struct TYPE_3__ {int /*<<< orphan*/  static_pass_number; } ;

/* Variables and functions */
 int TDF_GRAPH ; 
 int TDI_end ; 
 int /*<<< orphan*/  TV_DUMP ; 
 scalar_t__ dump_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_combine_total_stats (scalar_t__) ; 
 int /*<<< orphan*/  dump_end (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dump_file ; 
 scalar_t__ dump_initialized_p (int) ; 
 int /*<<< orphan*/  end_branch_prob () ; 
 int /*<<< orphan*/  finish_graph_dump_file (char*) ; 
 scalar_t__ flag_branch_probabilities ; 
 scalar_t__ flag_test_coverage ; 
 int /*<<< orphan*/  free (char*) ; 
 struct dump_file_info* get_dump_file_info (int) ; 
 char* get_dump_file_name (int) ; 
 scalar_t__ graph_dump_format ; 
 scalar_t__ no_graph ; 
 scalar_t__ optimize ; 
 TYPE_2__ pass_combine ; 
 TYPE_1__ pass_profile ; 
 scalar_t__ profile_arc_flag ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
finish_optimization_passes (void)
{
  enum tree_dump_index i;
  struct dump_file_info *dfi;
  char *name;

  timevar_push (TV_DUMP);
  if (profile_arc_flag || flag_test_coverage || flag_branch_probabilities)
    {
      dump_file = dump_begin (pass_profile.static_pass_number, NULL);
      end_branch_prob ();
      if (dump_file)
	dump_end (pass_profile.static_pass_number, dump_file);
    }

  if (optimize > 0)
    {
      dump_file = dump_begin (pass_combine.static_pass_number, NULL);
      if (dump_file)
	{
	  dump_combine_total_stats (dump_file);
          dump_end (pass_combine.static_pass_number, dump_file);
	}
    }

  /* Do whatever is necessary to finish printing the graphs.  */
  if (graph_dump_format != no_graph)
    for (i = TDI_end; (dfi = get_dump_file_info (i)) != NULL; ++i)
      if (dump_initialized_p (i)
	  && (dfi->flags & TDF_GRAPH) != 0
	  && (name = get_dump_file_name (i)) != NULL)
	{
	  finish_graph_dump_file (name);
	  free (name);
	}

  timevar_pop (TV_DUMP);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; TYPE_3__ coverage; struct TYPE_13__* next; int /*<<< orphan*/  num_lines; int /*<<< orphan*/  lines; } ;
typedef  TYPE_1__ source_t ;
struct TYPE_14__ {int /*<<< orphan*/  name; struct TYPE_14__* next; } ;
typedef  TYPE_2__ function_t ;
typedef  TYPE_3__ coverage_t ;
typedef  int /*<<< orphan*/  coverage ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  XCNEWVEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accumulate_line_counts (TYPE_1__*) ; 
 int /*<<< orphan*/  add_line_counts (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bbg_file_name ; 
 int /*<<< orphan*/  create_file_names (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ flag_function_summary ; 
 scalar_t__ flag_gcov_file ; 
 int /*<<< orphan*/  fnotice (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  function_summary (TYPE_3__*,char*) ; 
 TYPE_2__* functions ; 
 int /*<<< orphan*/  line_t ; 
 char* make_gcov_file_name (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_lines (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ read_count_file () ; 
 scalar_t__ read_graph_file () ; 
 int /*<<< orphan*/  solve_flow_graph (TYPE_2__*) ; 
 TYPE_1__* sources ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
process_file (const char *file_name)
{
  source_t *src;
  function_t *fn;

  create_file_names (file_name);
  if (read_graph_file ())
    return;

  if (!functions)
    {
      fnotice (stderr, "%s:no functions found\n", bbg_file_name);
      return;
    }

  if (read_count_file ())
    return;

  for (fn = functions; fn; fn = fn->next)
    solve_flow_graph (fn);
  for (src = sources; src; src = src->next)
    src->lines = XCNEWVEC (line_t, src->num_lines);
  for (fn = functions; fn; fn = fn->next)
    {
      coverage_t coverage;

      memset (&coverage, 0, sizeof (coverage));
      coverage.name = fn->name;
      add_line_counts (flag_function_summary ? &coverage : NULL, fn);
      if (flag_function_summary)
	{
	  function_summary (&coverage, "Function");
	  fnotice (stdout, "\n");
	}
    }

  for (src = sources; src; src = src->next)
    {
      accumulate_line_counts (src);
      function_summary (&src->coverage, "File");
      if (flag_gcov_file)
	{
	  char *gcov_file_name = make_gcov_file_name (file_name, src->name);
	  FILE *gcov_file = fopen (gcov_file_name, "w");

	  if (gcov_file)
	    {
	      fnotice (stdout, "%s:creating '%s'\n",
		       src->name, gcov_file_name);
	      output_lines (gcov_file, src);
	      if (ferror (gcov_file))
		    fnotice (stderr, "%s:error writing output file '%s'\n",
			     src->name, gcov_file_name);
	      fclose (gcov_file);
	    }
	  else
	    fnotice (stderr, "%s:could not open output file '%s'\n",
		     src->name, gcov_file_name);
	  free (gcov_file_name);
	}
      fnotice (stdout, "\n");
    }
}
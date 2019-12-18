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
struct TYPE_2__ {char* (* decl_printable_name ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int TDF_BLOCKS ; 
 int TDF_DETAILS ; 
 int TDF_STATS ; 
 int /*<<< orphan*/  brief_dump_cfg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  dump_cfg_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_function_to_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 TYPE_1__ lang_hooks ; 
 int last_basic_block ; 
 int n_basic_blocks ; 
 int n_edges ; 
 char* stub1 (int /*<<< orphan*/ ,int) ; 

void
dump_tree_cfg (FILE *file, int flags)
{
  if (flags & TDF_DETAILS)
    {
      const char *funcname
	= lang_hooks.decl_printable_name (current_function_decl, 2);

      fputc ('\n', file);
      fprintf (file, ";; Function %s\n\n", funcname);
      fprintf (file, ";; \n%d basic blocks, %d edges, last basic block %d.\n\n",
	       n_basic_blocks, n_edges, last_basic_block);

      brief_dump_cfg (file);
      fprintf (file, "\n");
    }

  if (flags & TDF_STATS)
    dump_cfg_stats (file);

  dump_function_to_file (current_function_decl, file, flags | TDF_BLOCKS);
}
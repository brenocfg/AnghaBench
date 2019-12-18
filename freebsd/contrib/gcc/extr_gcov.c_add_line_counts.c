#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {unsigned int index; TYPE_7__* lines; struct TYPE_24__* next; } ;
typedef  TYPE_6__ source_t ;
struct TYPE_23__ {TYPE_11__* branches; TYPE_10__* blocks; } ;
struct TYPE_25__ {int exists; TYPE_5__ u; scalar_t__ count; } ;
typedef  TYPE_7__ line_t ;
struct TYPE_26__ {unsigned int num_blocks; size_t line; int /*<<< orphan*/  name; TYPE_4__* src; int /*<<< orphan*/  blocks_executed; TYPE_10__* blocks; } ;
typedef  TYPE_8__ function_t ;
struct TYPE_27__ {int /*<<< orphan*/  lines_executed; int /*<<< orphan*/  lines; } ;
typedef  TYPE_9__ coverage_t ;
struct TYPE_20__ {unsigned int ident; int /*<<< orphan*/ * arc; } ;
struct TYPE_19__ {unsigned int* encoding; unsigned int num; } ;
struct TYPE_21__ {TYPE_2__ cycle; TYPE_1__ line; } ;
struct TYPE_17__ {TYPE_11__* succ; struct TYPE_17__* chain; TYPE_3__ u; scalar_t__ count; } ;
typedef  TYPE_10__ block_t ;
struct TYPE_18__ {int /*<<< orphan*/  is_unconditional; struct TYPE_18__* line_next; struct TYPE_18__* succ_next; } ;
typedef  TYPE_11__ arc_t ;
struct TYPE_22__ {TYPE_7__* lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_branch_counts (TYPE_9__*,TYPE_11__*) ; 
 int /*<<< orphan*/  bbg_file_name ; 
 scalar_t__ flag_all_blocks ; 
 scalar_t__ flag_branches ; 
 int /*<<< orphan*/  fnotice (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 TYPE_6__* sources ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
add_line_counts (coverage_t *coverage, function_t *fn)
{
  unsigned ix;
  line_t *line = NULL; /* This is propagated from one iteration to the
			  next.  */

  /* Scan each basic block.  */
  for (ix = 0; ix != fn->num_blocks; ix++)
    {
      block_t *block = &fn->blocks[ix];
      unsigned *encoding;
      const source_t *src = NULL;
      unsigned jx;

      if (block->count && ix && ix + 1 != fn->num_blocks)
	fn->blocks_executed++;
      for (jx = 0, encoding = block->u.line.encoding;
	   jx != block->u.line.num; jx++, encoding++)
	if (!*encoding)
	  {
	    unsigned src_n = *++encoding;

	    for (src = sources; src->index != src_n; src = src->next)
	      continue;
	    jx++;
	  }
	else
	  {
	    line = &src->lines[*encoding];

	    if (coverage)
	      {
		if (!line->exists)
		  coverage->lines++;
		if (!line->count && block->count)
		  coverage->lines_executed++;
	      }
	    line->exists = 1;
	    line->count += block->count;
	  }
      free (block->u.line.encoding);
      block->u.cycle.arc = NULL;
      block->u.cycle.ident = ~0U;

      if (!ix || ix + 1 == fn->num_blocks)
	/* Entry or exit block */;
      else if (flag_all_blocks)
	{
	  line_t *block_line = line ? line : &fn->src->lines[fn->line];

	  block->chain = block_line->u.blocks;
	  block_line->u.blocks = block;
	}
      else if (flag_branches)
	{
	  arc_t *arc;

	  for (arc = block->succ; arc; arc = arc->succ_next)
	    {
	      arc->line_next = line->u.branches;
	      line->u.branches = arc;
	      if (coverage && !arc->is_unconditional)
		add_branch_counts (coverage, arc);
	    }
	}
    }
  if (!line)
    fnotice (stderr, "%s:no lines for '%s'\n", bbg_file_name, fn->name);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_11__ {int index; int frequency; } ;
struct TYPE_10__ {int flags; TYPE_2__* dest; TYPE_2__* src; } ;

/* Variables and functions */
 int EDGE_COMPLEX ; 
 int EDGE_DFS_BACK ; 
 scalar_t__ dump_file ; 
 TYPE_1__* find_best_predecessor (TYPE_2__*) ; 
 TYPE_1__* find_best_successor (TYPE_2__*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 scalar_t__ seen (TYPE_2__*) ; 

__attribute__((used)) static int
find_trace (basic_block bb, basic_block *trace)
{
  int i = 0;
  edge e;

  if (dump_file)
    fprintf (dump_file, "Trace seed %i [%i]", bb->index, bb->frequency);

  while ((e = find_best_predecessor (bb)) != NULL)
    {
      basic_block bb2 = e->src;
      if (seen (bb2) || (e->flags & (EDGE_DFS_BACK | EDGE_COMPLEX))
	  || find_best_successor (bb2) != e)
	break;
      if (dump_file)
	fprintf (dump_file, ",%i [%i]", bb->index, bb->frequency);
      bb = bb2;
    }
  if (dump_file)
    fprintf (dump_file, " forward %i [%i]", bb->index, bb->frequency);
  trace[i++] = bb;

  /* Follow the trace in forward direction.  */
  while ((e = find_best_successor (bb)) != NULL)
    {
      bb = e->dest;
      if (seen (bb) || (e->flags & (EDGE_DFS_BACK | EDGE_COMPLEX))
	  || find_best_predecessor (bb) != e)
	break;
      if (dump_file)
	fprintf (dump_file, ",%i [%i]", bb->index, bb->frequency);
      trace[i++] = bb;
    }
  if (dump_file)
    fprintf (dump_file, "\n");
  return i;
}
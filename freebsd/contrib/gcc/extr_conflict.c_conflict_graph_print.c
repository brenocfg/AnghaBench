#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct print_context {int reg; scalar_t__ started; int /*<<< orphan*/ * fp; } ;
typedef  TYPE_1__* conflict_graph ;
struct TYPE_4__ {int num_regs; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  conflict_graph_enum (TYPE_1__*,int,int /*<<< orphan*/ *,struct print_context*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_conflict ; 

void
conflict_graph_print (conflict_graph graph, FILE *fp)
{
  int reg;
  struct print_context context;

  context.fp = fp;
  fprintf (fp, "Conflicts:\n");

  /* Loop over registers supported in this graph.  */
  for (reg = 0; reg < graph->num_regs; ++reg)
    {
      context.reg = reg;
      context.started = 0;

      /* Scan the conflicts for reg, printing as we go.  A label for
	 this line will be printed the first time a conflict is
	 printed for the reg; we won't start a new line if this reg
	 has no conflicts.  */
      conflict_graph_enum (graph, reg, &print_conflict, &context);

      /* If this reg does have conflicts, end the line.  */
      if (context.started)
	fputc ('\n', fp);
    }
}
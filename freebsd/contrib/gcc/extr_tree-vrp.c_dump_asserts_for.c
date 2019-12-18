#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_4__* assert_locus_t ;
struct TYPE_11__ {TYPE_3__* dest; TYPE_2__* src; } ;
struct TYPE_10__ {struct TYPE_10__* next; int /*<<< orphan*/  val; scalar_t__ comp_code; TYPE_5__* e; TYPE_1__* bb; int /*<<< orphan*/  si; } ;
struct TYPE_9__ {int index; } ;
struct TYPE_8__ {int index; } ;
struct TYPE_7__ {int index; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 TYPE_4__** asserts_for ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_edge_info (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** tree_code_name ; 

void
dump_asserts_for (FILE *file, tree name)
{
  assert_locus_t loc;

  fprintf (file, "Assertions to be inserted for ");
  print_generic_expr (file, name, 0);
  fprintf (file, "\n");

  loc = asserts_for[SSA_NAME_VERSION (name)];
  while (loc)
    {
      fprintf (file, "\t");
      print_generic_expr (file, bsi_stmt (loc->si), 0);
      fprintf (file, "\n\tBB #%d", loc->bb->index);
      if (loc->e)
	{
	  fprintf (file, "\n\tEDGE %d->%d", loc->e->src->index,
	           loc->e->dest->index);
	  dump_edge_info (file, loc->e, 0);
	}
      fprintf (file, "\n\tPREDICATE: ");
      print_generic_expr (file, name, 0);
      fprintf (file, " %s ", tree_code_name[(int)loc->comp_code]);
      print_generic_expr (file, loc->val, 0);
      fprintf (file, "\n\n");
      loc = loc->next;
    }

  fprintf (file, "\n");
}
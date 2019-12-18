#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* value_set_t ;
typedef  TYPE_2__* value_set_node_t ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  expr; } ;
struct TYPE_4__ {TYPE_2__* head; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  get_value_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_value_set (FILE *outfile, value_set_t set,
		 const char *setname, int blockindex)
{
  value_set_node_t node;
  fprintf (outfile, "%s[%d] := { ", setname, blockindex);
  if (set)
    {
      for (node = set->head;
	   node;
	   node = node->next)
	{
	  print_generic_expr (outfile, node->expr, 0);

	  fprintf (outfile, " (");
	  print_generic_expr (outfile, get_value_handle (node->expr), 0);
	  fprintf (outfile, ") ");

	  if (node->next)
	    fprintf (outfile, ", ");
	}
    }

  fprintf (outfile, " }\n");
}
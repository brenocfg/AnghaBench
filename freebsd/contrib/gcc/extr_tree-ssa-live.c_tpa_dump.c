#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tpa_p ;
struct TYPE_8__ {int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TDF_SLIM ; 
 int TPA_NONE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  partition_to_var (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpa_find_tree (TYPE_1__*,int) ; 
 int tpa_first_partition (TYPE_1__*,int) ; 
 int tpa_next_partition (TYPE_1__*,int) ; 
 int tpa_num_trees (TYPE_1__*) ; 
 int /*<<< orphan*/  tpa_tree (TYPE_1__*,int) ; 

void
tpa_dump (FILE *f, tpa_p tpa)
{
  int x, i;

  if (!tpa)
    return;

  for (x = 0; x < tpa_num_trees (tpa); x++)
    {
      print_generic_expr (f, tpa_tree (tpa, x), TDF_SLIM);
      fprintf (f, " : (");
      for (i = tpa_first_partition (tpa, x); 
	   i != TPA_NONE;
	   i = tpa_next_partition (tpa, i))
	{
	  fprintf (f, "(%d)",i);
	  print_generic_expr (f, partition_to_var (tpa->map, i), TDF_SLIM);
	  fprintf (f, " ");

#ifdef ENABLE_CHECKING
	  if (tpa_find_tree (tpa, i) != x)
	    fprintf (f, "**find tree incorrectly set** ");
#endif

	}
      fprintf (f, ")\n");
    }
  fflush (f);
}
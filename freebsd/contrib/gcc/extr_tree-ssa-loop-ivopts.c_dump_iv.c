#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iv {scalar_t__ biv_p; scalar_t__ base_object; scalar_t__ base; scalar_t__ step; scalar_t__ ssa_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void
dump_iv (FILE *file, struct iv *iv)
{
  if (iv->ssa_name)
    {
      fprintf (file, "ssa name ");
      print_generic_expr (file, iv->ssa_name, TDF_SLIM);
      fprintf (file, "\n");
    }

  fprintf (file, "  type ");
  print_generic_expr (file, TREE_TYPE (iv->base), TDF_SLIM);
  fprintf (file, "\n");

  if (iv->step)
    {
      fprintf (file, "  base ");
      print_generic_expr (file, iv->base, TDF_SLIM);
      fprintf (file, "\n");

      fprintf (file, "  step ");
      print_generic_expr (file, iv->step, TDF_SLIM);
      fprintf (file, "\n");
    }
  else
    {
      fprintf (file, "  invariant ");
      print_generic_expr (file, iv->base, TDF_SLIM);
      fprintf (file, "\n");
    }

  if (iv->base_object)
    {
      fprintf (file, "  base object ");
      print_generic_expr (file, iv->base_object, TDF_SLIM);
      fprintf (file, "\n");
    }

  if (iv->biv_p)
    fprintf (file, "  is a biv\n");
}
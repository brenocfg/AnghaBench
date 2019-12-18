#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* subvar_t ;
struct TYPE_3__ {int /*<<< orphan*/  var; struct TYPE_3__* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* get_subvars_for_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dump_subvars_for (FILE *file, tree var)
{
  subvar_t sv = get_subvars_for_var (var);

  if (!sv)
    return;

  fprintf (file, "{ ");

  for (; sv; sv = sv->next)
    {
      print_generic_expr (file, sv->var, dump_flags);
      fprintf (file, " ");
    }

  fprintf (file, "}");
}
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
struct iv_use {int id; int type; scalar_t__ related_cands; int /*<<< orphan*/  iv; int /*<<< orphan*/ * op_p; int /*<<< orphan*/  stmt; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TDF_SLIM ; 
#define  USE_ADDRESS 130 
#define  USE_COMPARE 129 
#define  USE_NONLINEAR_EXPR 128 
 int /*<<< orphan*/  dump_bitmap (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dump_iv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dump_use (FILE *file, struct iv_use *use)
{
  fprintf (file, "use %d\n", use->id);

  switch (use->type)
    {
    case USE_NONLINEAR_EXPR:
      fprintf (file, "  generic\n");
      break;

    case USE_ADDRESS:
      fprintf (file, "  address\n");
      break;

    case USE_COMPARE:
      fprintf (file, "  compare\n");
      break;

    default:
      gcc_unreachable ();
    }

  fprintf (file, "  in statement ");
  print_generic_expr (file, use->stmt, TDF_SLIM);
  fprintf (file, "\n");

  fprintf (file, "  at position ");
  if (use->op_p)
    print_generic_expr (file, *use->op_p, TDF_SLIM);
  fprintf (file, "\n");

  dump_iv (file, use->iv);

  if (use->related_cands)
    {
      fprintf (file, "  related candidates ");
      dump_bitmap (file, use->related_cands);
    }
}
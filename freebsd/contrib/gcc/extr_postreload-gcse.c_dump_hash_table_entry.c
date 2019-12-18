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
struct occr {struct occr* next; int /*<<< orphan*/  insn; } ;
struct expr {int hash; struct occr* avail_occr; int /*<<< orphan*/  expr; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_rtl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rtl_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_hash_table_entry (void **slot, void *filep)
{
  struct expr *expr = (struct expr *) *slot;
  FILE *file = (FILE *) filep;
  struct occr *occr;

  fprintf (file, "expr: ");
  print_rtl (file, expr->expr);
  fprintf (file,"\nhashcode: %u\n", expr->hash);
  fprintf (file,"list of occurrences:\n");
  occr = expr->avail_occr;
  while (occr)
    {
      rtx insn = occr->insn;
      print_rtl_single (file, insn);
      fprintf (file, "\n");
      occr = occr->next;
    }
  fprintf (file, "\n");
  return 1;
}
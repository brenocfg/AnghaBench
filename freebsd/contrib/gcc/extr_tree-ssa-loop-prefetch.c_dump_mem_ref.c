#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mem_ref {scalar_t__ write_p; int /*<<< orphan*/  delta; TYPE_1__* group; } ;
struct TYPE_2__ {int /*<<< orphan*/  step; int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* HOST_WIDE_INT_PRINT_DEC ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/ * dump_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_mem_ref (FILE *file, struct mem_ref *ref)
{
  fprintf (file, "Reference %p:\n", (void *) ref);

  fprintf (file, "  group %p (base ", (void *) ref->group);
  print_generic_expr (file, ref->group->base, TDF_SLIM);
  fprintf (file, ", step ");
  fprintf (file, HOST_WIDE_INT_PRINT_DEC, ref->group->step);
  fprintf (file, ")\n");

  fprintf (dump_file, "  delta ");
  fprintf (file, HOST_WIDE_INT_PRINT_DEC, ref->delta);
  fprintf (file, "\n");

  fprintf (file, "  %s\n", ref->write_p ? "write" : "read");

  fprintf (file, "\n");
}
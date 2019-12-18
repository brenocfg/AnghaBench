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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_value_range (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 size_t num_ssa_names ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssa_name (size_t) ; 
 scalar_t__* vr_value ; 

void
dump_all_value_ranges (FILE *file)
{
  size_t i;

  for (i = 0; i < num_ssa_names; i++)
    {
      if (vr_value[i])
	{
	  print_generic_expr (file, ssa_name (i), 0);
	  fprintf (file, ": ");
	  dump_value_range (file, vr_value[i]);
	  fprintf (file, "\n");
	}
    }

  fprintf (file, "\n");
}
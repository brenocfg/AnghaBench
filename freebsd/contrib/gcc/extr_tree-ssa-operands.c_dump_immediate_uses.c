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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dump_immediate_uses_for (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 unsigned int num_ssa_names ; 
 int /*<<< orphan*/  ssa_name (unsigned int) ; 

void
dump_immediate_uses (FILE *file)
{
  tree var;
  unsigned int x;

  fprintf (file, "Immediate_uses: \n\n");
  for (x = 1; x < num_ssa_names; x++)
    {
      var = ssa_name(x);
      if (!var)
        continue;
      dump_immediate_uses_for (file, var);
    }
}
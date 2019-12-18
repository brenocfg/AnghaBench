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
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int max_regno ; 
 scalar_t__* reg_renumber ; 
 scalar_t__* regs_ever_live ; 

void
dump_global_regs (FILE *file)
{
  int i, j;

  fprintf (file, ";; Register dispositions:\n");
  for (i = FIRST_PSEUDO_REGISTER, j = 0; i < max_regno; i++)
    if (reg_renumber[i] >= 0)
      {
	fprintf (file, "%d in %d  ", i, reg_renumber[i]);
	if (++j % 6 == 0)
	  fprintf (file, "\n");
      }

  fprintf (file, "\n\n;; Hard regs used: ");
  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    if (regs_ever_live[i])
      fprintf (file, " %d", i);
  fprintf (file, "\n\n");
}
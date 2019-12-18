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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int) ; 
 int max_regno ; 
 int* reg_renumber ; 

void
dump_local_alloc (FILE *file)
{
  int i;
  for (i = FIRST_PSEUDO_REGISTER; i < max_regno; i++)
    if (reg_renumber[i] != -1)
      fprintf (file, ";; Register %d in %d.\n", i, reg_renumber[i]);
}
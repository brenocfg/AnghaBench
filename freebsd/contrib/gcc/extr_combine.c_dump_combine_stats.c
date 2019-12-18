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
 int combine_attempts ; 
 int combine_extras ; 
 int combine_merges ; 
 int combine_successes ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int) ; 

void
dump_combine_stats (FILE *file)
{
  fprintf
    (file,
     ";; Combiner statistics: %d attempts, %d substitutions (%d requiring new space),\n;; %d successes.\n\n",
     combine_attempts, combine_merges, combine_extras, combine_successes);
}
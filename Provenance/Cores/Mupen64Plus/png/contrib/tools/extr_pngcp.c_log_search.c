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
struct display {unsigned int nsp; int /*<<< orphan*/  best_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SIZE ; 
 int /*<<< orphan*/  print_search_results (struct display*) ; 

__attribute__((used)) static void
log_search(struct display *dp, unsigned int log_depth)
{
   /* Log, and reset, the search so far: */
   if (dp->nsp/*next entry to change*/ <= log_depth)
   {
      print_search_results(dp);
      /* Start again with this entry: */
      dp->best_size = MAX_SIZE;
   }
}
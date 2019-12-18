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

/* Variables and functions */
 int NUM_BUCKETS ; 
 scalar_t__ free_phinode_count ; 
 int /*<<< orphan*/ ** free_phinodes ; 

void
fini_phinodes (void)
{
  int i;

  for (i = 0; i < NUM_BUCKETS - 2; i++)
    free_phinodes[i] = NULL;
  free_phinode_count = 0;
}
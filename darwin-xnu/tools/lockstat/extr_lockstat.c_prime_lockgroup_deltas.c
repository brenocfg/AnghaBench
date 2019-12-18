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
typedef  int /*<<< orphan*/  lockgroup_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 void* calloc (int,int) ; 
 int count ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * lockgroup_deltas ; 
 int /*<<< orphan*/  lockgroup_info ; 
 int /*<<< orphan*/ * lockgroup_start ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

void
prime_lockgroup_deltas(void)
{
	lockgroup_start = calloc(count, sizeof(lockgroup_info_t));
	if (lockgroup_start == NULL) {
		fprintf(stderr, "Can't allocate memory for lockgroup info\n");
		exit (EXIT_FAILURE);
	}
	memcpy(lockgroup_start, lockgroup_info, count * sizeof(lockgroup_info_t));

	lockgroup_deltas = calloc(count,  sizeof(lockgroup_info_t));
	if (lockgroup_deltas == NULL) {
		fprintf(stderr, "Can't allocate memory for lockgroup info\n");
		exit (EXIT_FAILURE);
	}
}
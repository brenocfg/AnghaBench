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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static boolean_t
is_thrashing(uint32_t added, uint32_t found, uint32_t threshold)
{
	/* Ignore normal activity below the threshold. */
	if (added < threshold || found < threshold)
		return FALSE;

	/*
	 * When thrashing in a way that we can mitigate, most of the pages read
	 * into the file cache were recently evicted, and 'found' will be close
	 * to 'added'.
	 *
	 * When replacing the current working set because a new app is
	 * launched, we see very high read traffic with sporadic phantom cache
	 * hits.
	 *
	 * This is not thrashing, or freeing up memory wouldn't help much
	 * anyway.
	 */
	if (found < added / 2)
		return FALSE;

	return TRUE;
}
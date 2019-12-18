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
struct perf_evlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct perf_evlist*) ; 
 int /*<<< orphan*/  perf_evlist__exit (struct perf_evlist*) ; 
 int /*<<< orphan*/  perf_evlist__purge (struct perf_evlist*) ; 

void perf_evlist__delete(struct perf_evlist *evlist)
{
	perf_evlist__purge(evlist);
	perf_evlist__exit(evlist);
	free(evlist);
}
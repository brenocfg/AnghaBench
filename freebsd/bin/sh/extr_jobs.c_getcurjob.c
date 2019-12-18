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
struct job {scalar_t__ state; scalar_t__ used; struct job* next; } ;

/* Variables and functions */
 scalar_t__ JOBSTOPPED ; 
 struct job* jobmru ; 

__attribute__((used)) static struct job *
getcurjob(struct job *nj)
{
	struct job *jp;

	/* Try to find a stopped one.. */
	for (jp = jobmru; jp != NULL; jp = jp->next)
		if (jp->used && jp != nj && jp->state == JOBSTOPPED)
			return (jp);
	/* Otherwise the most recently used job that isn't `nj' */
	for (jp = jobmru; jp != NULL; jp = jp->next)
		if (jp->used && jp != nj)
			return (jp);

	return (NULL);
}
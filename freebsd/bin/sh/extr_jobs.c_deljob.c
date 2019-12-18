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
struct job {struct job* next; } ;

/* Variables and functions */
 struct job* jobmru ; 

__attribute__((used)) static void
deljob(struct job *j)
{
	struct job *jp, *prev;

	for (prev = NULL, jp = jobmru; jp != NULL; prev = jp, jp = jp->next) {
		if (jp == j) {
			if (prev != NULL)
				prev->next = jp->next;
			else
				jobmru = jp->next;
			return;
		}
	}
}
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
struct match {struct match* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct match*) ; 

__attribute__((used)) static void freelist(struct match *head)
{
	struct match *match, *next;
	for (match=head->next; match; match=next) {
		next = match->next;
		free(match);
	}
}
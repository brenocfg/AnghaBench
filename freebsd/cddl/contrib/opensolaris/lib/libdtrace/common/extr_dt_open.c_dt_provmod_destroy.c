#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* dp_name; struct TYPE_4__* dp_next; } ;
typedef  TYPE_1__ dt_provmod_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
dt_provmod_destroy(dt_provmod_t **provmod)
{
	dt_provmod_t *next, *current;

	for (current = *provmod; current != NULL; current = next) {
		next = current->dp_next;
		free(current->dp_name);
		free(current);
	}

	*provmod = NULL;
}
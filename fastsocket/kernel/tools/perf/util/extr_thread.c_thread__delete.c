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
struct thread {struct thread* comm; int /*<<< orphan*/  mg; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct thread*) ; 
 int /*<<< orphan*/  map_groups__exit (int /*<<< orphan*/ *) ; 

void thread__delete(struct thread *self)
{
	map_groups__exit(&self->mg);
	free(self->comm);
	free(self);
}
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
struct thread {int comm_set; int /*<<< orphan*/ * comm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int thread__set_comm(struct thread *self, const char *comm)
{
	int err;

	if (self->comm)
		free(self->comm);
	self->comm = strdup(comm);
	err = self->comm == NULL ? -ENOMEM : 0;
	if (!err) {
		self->comm_set = true;
	}
	return err;
}
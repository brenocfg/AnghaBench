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
struct thread {int comm_set; int /*<<< orphan*/  mg; scalar_t__ comm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAP__NR_TYPES ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ map_groups__clone (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strdup (scalar_t__) ; 

int thread__fork(struct thread *self, struct thread *parent)
{
	int i;

	if (parent->comm_set) {
		if (self->comm)
			free(self->comm);
		self->comm = strdup(parent->comm);
		if (!self->comm)
			return -ENOMEM;
		self->comm_set = true;
	}

	for (i = 0; i < MAP__NR_TYPES; ++i)
		if (map_groups__clone(&self->mg, &parent->mg, i) < 0)
			return -ENOMEM;
	return 0;
}
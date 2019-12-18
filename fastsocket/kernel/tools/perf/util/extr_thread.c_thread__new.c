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
struct thread {int pid; scalar_t__ comm; int /*<<< orphan*/  mg; } ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  map_groups__init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (scalar_t__,int,char*,int) ; 
 struct thread* zalloc (int) ; 

struct thread *thread__new(pid_t pid)
{
	struct thread *self = zalloc(sizeof(*self));

	if (self != NULL) {
		map_groups__init(&self->mg);
		self->pid = pid;
		self->comm = malloc(32);
		if (self->comm)
			snprintf(self->comm, 32, ":%d", self->pid);
	}

	return self;
}
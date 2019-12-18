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
struct TYPE_4__ {scalar_t__ fd; struct TYPE_4__* next; struct TYPE_4__* inb; } ;
typedef  TYPE_1__ Source ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 TYPE_1__* cursource ; 
 int /*<<< orphan*/  dofree (TYPE_1__*) ; 

void
unsetsource(void)
{
	Source *s = cursource;

	if (s->fd>=0) {
		close(s->fd);
		dofree(s->inb);
	}
	cursource = s->next;
	dofree(s);
}
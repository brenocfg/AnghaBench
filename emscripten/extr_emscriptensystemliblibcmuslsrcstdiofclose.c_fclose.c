#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int flags; int (* close ) (TYPE_2__*) ;struct TYPE_12__* getln_buf; struct TYPE_12__* next; TYPE_1__* prev; } ;
struct TYPE_11__ {TYPE_2__* next; } ;
typedef  TYPE_2__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_2__*) ; 
 int F_PERM ; 
 TYPE_2__** __ofl_lock () ; 
 int /*<<< orphan*/  __ofl_unlock () ; 
 int /*<<< orphan*/  __unlist_locked_file (TYPE_2__*) ; 
 int fflush (TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int stub1 (TYPE_2__*) ; 

int fclose(FILE *f)
{
	int r;
	int perm;
	
	FLOCK(f);

	__unlist_locked_file(f);

	if (!(perm = f->flags & F_PERM)) {
		FILE **head = __ofl_lock();
		if (f->prev) f->prev->next = f->next;
		if (f->next) f->next->prev = f->prev;
		if (*head == f) *head = f->next;
		__ofl_unlock();
	}

	r = fflush(f);
	r |= f->close(f);

	if (f->getln_buf) free(f->getln_buf);
	if (!perm) free(f);
	else FUNLOCK(f);

	return r;
}
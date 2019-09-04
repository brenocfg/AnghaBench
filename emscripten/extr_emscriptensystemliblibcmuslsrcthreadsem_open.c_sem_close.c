#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sem_t ;
struct TYPE_2__ {scalar_t__ ino; int /*<<< orphan*/ * sem; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ ) ; 
 int SEM_NSEMS_MAX ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* semtab ; 

int sem_close(sem_t *sem)
{
	int i;
	LOCK(lock);
	for (i=0; i<SEM_NSEMS_MAX && semtab[i].sem != sem; i++);
	if (!--semtab[i].refcnt) {
		semtab[i].sem = 0;
		semtab[i].ino = 0;
	}
	UNLOCK(lock);
	munmap(sem, sizeof *sem);
	return 0;
}
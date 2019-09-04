#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mp_call_t ;
struct TYPE_3__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ mp_call_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int MP_CPUS_CALL_BUFS_PER_CPU ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  mp_call_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* mp_cpus_call_head ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mp_cpus_call_cpu_init(int cpu)
{
	int		i;
	mp_call_queue_t	*cqp = &mp_cpus_call_head[cpu];
	mp_call_t	*callp;

	simple_lock_init(&cqp->lock, 0);
	queue_init(&cqp->queue);
	for (i = 0; i < MP_CPUS_CALL_BUFS_PER_CPU; i++) {
		callp = (mp_call_t *) kalloc(sizeof(mp_call_t));
		mp_call_free(callp);
	}

	DBG("mp_cpus_call_init(%d) done\n", cpu);
}
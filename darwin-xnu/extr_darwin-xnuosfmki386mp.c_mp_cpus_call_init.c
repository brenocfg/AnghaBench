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
struct TYPE_3__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ mp_call_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 TYPE_1__ mp_cpus_call_freelist ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mp_cpus_call_init(void)
{
	mp_call_queue_t	*cqp = &mp_cpus_call_freelist;

	DBG("mp_cpus_call_init()\n");
	simple_lock_init(&cqp->lock, 0);
	queue_init(&cqp->queue);
}
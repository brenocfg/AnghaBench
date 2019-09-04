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
typedef  TYPE_1__* aio_workq_t ;
typedef  int /*<<< orphan*/  aio_workq_entry ;
struct TYPE_4__ {scalar_t__ aioq_count; int /*<<< orphan*/  aioq_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_AIO_WORKQ_LOCK_OWNED (TYPE_1__*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_workq_link ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void		
aio_workq_add_entry_locked(aio_workq_t queue, aio_workq_entry *entryp)
{
	ASSERT_AIO_WORKQ_LOCK_OWNED(queue);

	TAILQ_INSERT_TAIL(&queue->aioq_entries, entryp, aio_workq_link);
	if (queue->aioq_count  < 0) {
		panic("Negative count on a queue.\n");
	}
	queue->aioq_count++;
}
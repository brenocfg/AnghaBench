#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_10__* dev; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ slave_t ;
struct TYPE_13__ {int /*<<< orphan*/  num_slaves; int /*<<< orphan*/  all_slaves; } ;
typedef  TYPE_2__ slave_queue_t ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IFF_SLAVE ; 
 TYPE_1__* __eql_find_slave_dev (TYPE_2__*,TYPE_10__*) ; 
 int /*<<< orphan*/  eql_is_full (TYPE_2__*) ; 
 int /*<<< orphan*/  eql_kill_one_slave (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __eql_insert_slave(slave_queue_t *queue, slave_t *slave)
{
	if (!eql_is_full(queue)) {
		slave_t *duplicate_slave = NULL;

		duplicate_slave = __eql_find_slave_dev(queue, slave->dev);
		if (duplicate_slave)
			eql_kill_one_slave(queue, duplicate_slave);

		list_add(&slave->list, &queue->all_slaves);
		queue->num_slaves++;
		slave->dev->flags |= IFF_SLAVE;

		return 0;
	}

	return -ENOSPC;
}
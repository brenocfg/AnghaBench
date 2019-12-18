#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num_slaves; int /*<<< orphan*/  master_dev; } ;
typedef  TYPE_1__ slave_queue_t ;
struct TYPE_6__ {scalar_t__ max_slaves; } ;
typedef  TYPE_2__ equalizer_t ;

/* Variables and functions */
 TYPE_2__* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int eql_is_full(slave_queue_t *queue)
{
	equalizer_t *eql = netdev_priv(queue->master_dev);

	if (queue->num_slaves >= eql->max_slaves)
		return 1;
	return 0;
}
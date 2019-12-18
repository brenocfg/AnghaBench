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
struct i2400m {TYPE_1__* rx_roq; scalar_t__ rx_reorder; } ;
struct TYPE_2__ {struct TYPE_2__* log; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int I2400M_RO_CIN ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void i2400m_rx_release(struct i2400m *i2400m)
{
	if (i2400m->rx_reorder) {
		unsigned itr;
		for(itr = 0; itr < I2400M_RO_CIN + 1; itr++)
			__skb_queue_purge(&i2400m->rx_roq[itr].queue);
		kfree(i2400m->rx_roq[0].log);
		kfree(i2400m->rx_roq);
	}
}
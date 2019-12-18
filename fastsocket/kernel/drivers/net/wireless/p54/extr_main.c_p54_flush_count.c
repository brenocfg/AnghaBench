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
struct p54_common {TYPE_1__* tx_stats; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned int P54_QUEUE_MGMT ; 
 unsigned int P54_QUEUE_NUM ; 

__attribute__((used)) static unsigned int p54_flush_count(struct p54_common *priv)
{
	unsigned int total = 0, i;

	BUILD_BUG_ON(P54_QUEUE_NUM > ARRAY_SIZE(priv->tx_stats));

	/*
	 * Because the firmware has the sole control over any frames
	 * in the P54_QUEUE_BEACON or P54_QUEUE_SCAN queues, they
	 * don't really count as pending or active.
	 */
	for (i = P54_QUEUE_MGMT; i < P54_QUEUE_NUM; i++)
		total += priv->tx_stats[i].len;
	return total;
}
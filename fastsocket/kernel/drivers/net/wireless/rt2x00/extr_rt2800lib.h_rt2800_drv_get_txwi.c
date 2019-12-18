#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rt2800_ops {int /*<<< orphan*/ * (* drv_get_txwi ) (struct queue_entry*) ;} ;
struct queue_entry {TYPE_3__* queue; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {TYPE_2__* rt2x00dev; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {struct rt2800_ops* drv; } ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (struct queue_entry*) ; 

__attribute__((used)) static inline __le32 *rt2800_drv_get_txwi(struct queue_entry *entry)
{
	const struct rt2800_ops *rt2800ops = entry->queue->rt2x00dev->ops->drv;

	return rt2800ops->drv_get_txwi(entry);
}
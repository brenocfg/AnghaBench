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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsQueue {int tail; int sizeMask; int head; TYPE_1__* cell; } ;
struct TYPE_2__ {int /*<<< orphan*/  tick; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_ERR_QUEUE_FULL ; 
 int /*<<< orphan*/  ZM_LV_1 ; 
 int /*<<< orphan*/  ZM_SUCCESS ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 

u16_t zfQueuePutNcs(zdev_t* dev, struct zsQueue* q, zbuf_t* buf, u32_t tick)
{
    u16_t ret = ZM_ERR_QUEUE_FULL;

    zm_msg0_mm(ZM_LV_1, "zfQueuePutNcs()");

    if (((q->tail+1)&q->sizeMask) != q->head)
    {
        q->cell[q->tail].buf = buf;
        q->cell[q->tail].tick = tick;
        q->tail = (q->tail+1) & q->sizeMask;
        ret = ZM_SUCCESS;
    }

    return ret;
}
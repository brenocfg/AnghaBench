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
typedef  int u8_t ;
typedef  int u16_t ;
struct zsQueue {int sizeMask; int tail; TYPE_1__* cell; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  tick; } ;

/* Variables and functions */
 scalar_t__ zfCompareDstwithBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

u8_t zfQueueRemovewithIndex(zdev_t* dev, struct zsQueue* q, u16_t index, u8_t* addr)
{
    u16_t next;
    u8_t mb = 0;

    //trace the whole queue to calculate more bit
    while ((next =((index+1)&q->sizeMask)) != q->tail)
    {
        q->cell[index].buf = q->cell[next].buf;
        q->cell[index].tick = q->cell[next].tick;

        if ((mb == 0) && (zfCompareDstwithBuf(dev,
                q->cell[next].buf, addr) == 0))
        {
            mb = 1;
        }

        index = next;
    }
    q->tail = (q->tail-1) & q->sizeMask;

    return mb;

}
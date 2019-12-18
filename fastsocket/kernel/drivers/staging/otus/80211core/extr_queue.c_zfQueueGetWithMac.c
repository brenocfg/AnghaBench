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
typedef  int u8_t ;
typedef  size_t u16_t ;
struct zsQueue {size_t head; size_t tail; size_t sizeMask; TYPE_1__* cell; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/  tick; } ;

/* Variables and functions */
 scalar_t__ zfCompareDstwithBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

zbuf_t* zfQueueGetWithMac(zdev_t* dev, struct zsQueue* q, u8_t* addr, u8_t* mb)
{
    zbuf_t* buf;
    zbuf_t* retBuf = NULL;
    u16_t index, next;
    zmw_declare_for_critical_section();

    *mb = 0;

    zmw_enter_critical_section(dev);

    index = q->head;

    while (1)
    {
        if (index != q->tail)
        {
            buf = q->cell[index].buf;

            //if buf's detination address == input addr
            if (zfCompareDstwithBuf(dev, buf, addr) == 0)
            {
                retBuf = buf;
                //Get it, and trace the whole queue to calculate more bit
                while ((next =((index+1)&q->sizeMask)) != q->tail)
                {
                    q->cell[index].buf = q->cell[next].buf;
                    q->cell[index].tick = q->cell[next].tick;

                    if ((*mb == 0) && (zfCompareDstwithBuf(dev,
                            q->cell[next].buf, addr) == 0))
                    {
                        *mb = 1;
                    }

                    index = next;
                }
                q->tail = (q->tail-1) & q->sizeMask;

                zmw_leave_critical_section(dev);
                return retBuf;
            }
            index = (index + 1) & q->sizeMask;
        } //if (index != q->tail)
        else
        {
            break;
        }
    }

    zmw_leave_critical_section(dev);

    return retBuf;

}
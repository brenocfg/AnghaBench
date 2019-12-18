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
struct zsQueue {size_t head; size_t tail; int sizeMask; TYPE_1__* cell; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

zbuf_t* zfQueueGet(zdev_t* dev, struct zsQueue* q)
{
    zbuf_t* buf = NULL;
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    if (q->head != q->tail)
    {
        buf = q->cell[q->head].buf;
        q->head = (q->head+1) & q->sizeMask;
    }

    zmw_leave_critical_section(dev);

    return buf;
}
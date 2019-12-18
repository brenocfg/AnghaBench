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
typedef  int u32_t ;
struct zsQueue {size_t head; size_t tail; int sizeMask; TYPE_1__* cell; } ;
struct TYPE_2__ {int tick; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_LV_0 ; 
 int ZM_MS_PER_TICK ; 
 int /*<<< orphan*/  zfwBufFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zm_msg0_mm (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfQueueAge(zdev_t* dev, struct zsQueue* q, u32_t tick, u32_t msAge)
{
    zbuf_t* buf;
    u32_t   buftick;
    zmw_declare_for_critical_section();

    while (1)
    {
        buf = NULL;
        zmw_enter_critical_section(dev);

        if (q->head != q->tail)
        {
            buftick = q->cell[q->head].tick;
            if (((tick - buftick)*ZM_MS_PER_TICK) > msAge)
            {
                buf = q->cell[q->head].buf;
                q->head = (q->head+1) & q->sizeMask;
            }
        }

        zmw_leave_critical_section(dev);

        if (buf != NULL)
        {
            zm_msg0_mm(ZM_LV_0, "Age frame in queue!");
            zfwBufFree(dev, buf, 0);
        }
        else
        {
            break;
        }
    }
    return;
}
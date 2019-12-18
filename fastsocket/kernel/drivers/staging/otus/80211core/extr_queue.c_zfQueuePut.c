#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  u16_t ;
struct zsQueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfQueuePutNcs (int /*<<< orphan*/ *,struct zsQueue*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

u16_t zfQueuePut(zdev_t* dev, struct zsQueue* q, zbuf_t* buf, u32_t tick)
{
    u16_t ret;
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);

    ret = zfQueuePutNcs(dev, q, buf, tick);

    zmw_leave_critical_section(dev);

    return ret;
}
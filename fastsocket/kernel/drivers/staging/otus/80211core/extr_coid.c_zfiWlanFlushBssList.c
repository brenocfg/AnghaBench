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

/* Variables and functions */
 int /*<<< orphan*/  zfBssInfoRefresh (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanFlushBssList(zdev_t* dev)
{
    zmw_declare_for_critical_section();

    zmw_enter_critical_section(dev);
    /* Call zfBssInfoRefresh() twice to remove all entry */
    zfBssInfoRefresh(dev, 1);
    zmw_leave_critical_section(dev);
}
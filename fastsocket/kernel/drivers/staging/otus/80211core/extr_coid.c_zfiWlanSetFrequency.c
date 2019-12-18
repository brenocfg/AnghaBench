#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  int u32_t ;
typedef  void* u16_t ;
struct TYPE_3__ {void* frequency; scalar_t__ autoSetFrequency; } ;
struct TYPE_4__ {TYPE_1__ ws; void* frequency; } ;

/* Variables and functions */
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zfCoreSetFrequency (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zmw_declare_for_critical_section () ; 
 int /*<<< orphan*/  zmw_enter_critical_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zmw_leave_critical_section (int /*<<< orphan*/ *) ; 

void zfiWlanSetFrequency(zdev_t* dev, u32_t frequency, u8_t bImmediate)
{
    zmw_get_wlan_dev(dev);

    zmw_declare_for_critical_section();

    if ( bImmediate )
    {
        zmw_enter_critical_section(dev);
        wd->frequency = (u16_t) (frequency/1000);
        zmw_leave_critical_section(dev);
        zfCoreSetFrequency(dev, wd->frequency);
    }
    else
    {
        zmw_enter_critical_section(dev);
        if( frequency == 0 )
        { // Auto select clean channel depend on wireless environment !
            wd->ws.autoSetFrequency = 0;
        }
        wd->ws.frequency = (u16_t) (frequency/1000);
        zmw_leave_critical_section(dev);
    }
}
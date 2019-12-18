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
struct TYPE_3__ {int cw_enable; int /*<<< orphan*/  cw_width; void* cw_mode; } ;
struct TYPE_4__ {int wlanMode; TYPE_1__ cwm; } ;

/* Variables and functions */
 void* CWM_MODE2040 ; 
 int /*<<< orphan*/  CWM_WIDTH20 ; 
 int /*<<< orphan*/  CWM_WIDTH40 ; 
#define  ZM_MODE_AP 131 
#define  ZM_MODE_IBSS 130 
#define  ZM_MODE_INFRASTRUCTURE 129 
#define  ZM_MODE_PSEUDO 128 
 TYPE_2__* wd ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfCwmInit(zdev_t* dev) {
    //u16_t i;
    zmw_get_wlan_dev(dev);

    switch (wd->wlanMode) {
    case ZM_MODE_AP:
        wd->cwm.cw_mode = CWM_MODE2040;
        wd->cwm.cw_width = CWM_WIDTH40;
        wd->cwm.cw_enable = 1;
        break;
    case ZM_MODE_INFRASTRUCTURE:
    case ZM_MODE_PSEUDO:
    case ZM_MODE_IBSS:
    default:
        wd->cwm.cw_mode = CWM_MODE2040;
        wd->cwm.cw_width = CWM_WIDTH20;
        wd->cwm.cw_enable = 1;
        break;
    }
}
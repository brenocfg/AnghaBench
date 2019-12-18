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
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */

u32_t zfRateCtrlUDPTP(zdev_t* dev, u16_t Rate, u32_t PER) {
    if ((PER < 100) && (Rate > 0) && PER)
        return 1168000/(((12304/Rate)+197)*(100+100*PER/(100-PER)));
    else
        return 0;
}
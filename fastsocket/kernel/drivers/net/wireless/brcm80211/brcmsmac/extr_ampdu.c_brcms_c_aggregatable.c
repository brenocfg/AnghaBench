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
typedef  size_t u8 ;
struct brcms_c_info {TYPE_1__* ampdu; } ;
struct TYPE_2__ {int* ini_enable; } ;

/* Variables and functions */

bool brcms_c_aggregatable(struct brcms_c_info *wlc, u8 tid)
{
	return wlc->ampdu->ini_enable[tid];
}
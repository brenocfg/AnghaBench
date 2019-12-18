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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_c_info {TYPE_1__* band; } ;
struct TYPE_2__ {int /*<<< orphan*/  phytype; } ;

/* Variables and functions */

u16 brcms_c_get_phy_type(struct brcms_c_info *wlc, int phyidx)
{
	return wlc->band->phytype;
}
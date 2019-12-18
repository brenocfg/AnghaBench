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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MgntActSet_RF_State (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_CHANGE_BY_PS ; 
 int /*<<< orphan*/  eRfSleep ; 

void rtl8225z4_rf_sleep(struct net_device *dev)
{
	MgntActSet_RF_State(dev, eRfSleep, RF_CHANGE_BY_PS);
}
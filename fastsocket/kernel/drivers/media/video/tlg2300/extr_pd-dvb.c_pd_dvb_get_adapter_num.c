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
struct TYPE_2__ {int num; } ;
struct pd_dvb_adapter {TYPE_1__ dvb_adap; } ;

/* Variables and functions */

int pd_dvb_get_adapter_num(struct pd_dvb_adapter *pd_dvb)
{
	return pd_dvb->dvb_adap.num;
}
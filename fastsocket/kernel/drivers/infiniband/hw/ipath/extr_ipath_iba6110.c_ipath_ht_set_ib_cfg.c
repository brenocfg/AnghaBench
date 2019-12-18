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
typedef  void* u32 ;
struct ipath_devdata {void* ipath_link_speed_enabled; void* ipath_link_width_enabled; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int IPATH_IB_CFG_LWID_ENB ; 
 int IPATH_IB_CFG_SPD_ENB ; 

__attribute__((used)) static int ipath_ht_set_ib_cfg(struct ipath_devdata *dd, int which, u32 val)
{
	int ret = 0;

	if (which == IPATH_IB_CFG_LWID_ENB)
		dd->ipath_link_width_enabled = val;
	else if (which == IPATH_IB_CFG_SPD_ENB)
		dd->ipath_link_speed_enabled = val;
	else
		ret = -ENOTSUPP;
	return ret;
}
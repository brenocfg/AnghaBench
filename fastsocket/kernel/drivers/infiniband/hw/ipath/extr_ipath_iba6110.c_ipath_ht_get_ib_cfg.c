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
struct ipath_devdata {int ipath_link_width_active; int ipath_link_speed_active; int ipath_link_width_enabled; int ipath_link_speed_enabled; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  IPATH_IB_CFG_LWID 131 
#define  IPATH_IB_CFG_LWID_ENB 130 
#define  IPATH_IB_CFG_SPD 129 
#define  IPATH_IB_CFG_SPD_ENB 128 

__attribute__((used)) static int ipath_ht_get_ib_cfg(struct ipath_devdata *dd, int which)
{
	int ret;

	switch (which) {
	case IPATH_IB_CFG_LWID:
		ret = dd->ipath_link_width_active;
		break;
	case IPATH_IB_CFG_SPD:
		ret = dd->ipath_link_speed_active;
		break;
	case IPATH_IB_CFG_LWID_ENB:
		ret = dd->ipath_link_width_enabled;
		break;
	case IPATH_IB_CFG_SPD_ENB:
		ret = dd->ipath_link_speed_enabled;
		break;
	default:
		ret =  -ENOTSUPP;
		break;
	}
	return ret;
}
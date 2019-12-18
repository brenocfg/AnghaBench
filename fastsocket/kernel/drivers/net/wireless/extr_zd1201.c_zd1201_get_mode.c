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
struct zd1201 {scalar_t__ monitor; TYPE_1__* usb; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
typedef  int __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IW_MODE_ADHOC ; 
 int IW_MODE_AUTO ; 
 int IW_MODE_INFRA ; 
 int IW_MODE_MASTER ; 
 int IW_MODE_MONITOR ; 
 int IW_MODE_REPEAT ; 
#define  ZD1201_PORTTYPE_AP 132 
#define  ZD1201_PORTTYPE_BSS 131 
#define  ZD1201_PORTTYPE_IBSS 130 
#define  ZD1201_PORTTYPE_PSEUDOIBSS 129 
#define  ZD1201_PORTTYPE_WDS 128 
 int /*<<< orphan*/  ZD1201_RID_CNFPORTTYPE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,short) ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_getconfig16 (struct zd1201*,int /*<<< orphan*/ ,short*) ; 

__attribute__((used)) static int zd1201_get_mode(struct net_device *dev,
    struct iw_request_info *info, __u32 *mode, char *extra)
{
	struct zd1201 *zd = netdev_priv(dev);
	short porttype;
	int err;

	err = zd1201_getconfig16(zd, ZD1201_RID_CNFPORTTYPE, &porttype);
	if (err)
		return err;
	switch(porttype) {
		case ZD1201_PORTTYPE_IBSS:
			*mode = IW_MODE_ADHOC;
			break;
		case ZD1201_PORTTYPE_BSS:
			*mode = IW_MODE_INFRA;
			break;
		case ZD1201_PORTTYPE_WDS:
			*mode = IW_MODE_REPEAT;
			break;
		case ZD1201_PORTTYPE_PSEUDOIBSS:
			*mode = 8;/* No Pseudo-IBSS... */
			break;
		case ZD1201_PORTTYPE_AP:
			*mode = IW_MODE_MASTER;
			break;
		default:
			dev_dbg(&zd->usb->dev, "Unknown porttype: %d\n",
			    porttype);
			*mode = IW_MODE_AUTO;
	}
	if (zd->monitor)
		*mode = IW_MODE_MONITOR;

	return 0;
}
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
struct zd1201 {int dummy; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {short value; int disabled; int fixed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD1201_RID_CNFRTSTHRESHOLD ; 
 short ZD1201_RTSMAX ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_getconfig16 (struct zd1201*,int /*<<< orphan*/ ,short*) ; 

__attribute__((used)) static int zd1201_get_rts(struct net_device *dev, struct iw_request_info *info,
    struct iw_param *rts, char *extra)
{
	struct zd1201 *zd = netdev_priv(dev);
	short rtst;
	int err;

	err = zd1201_getconfig16(zd, ZD1201_RID_CNFRTSTHRESHOLD, &rtst);
	if (err)
		return err;
	rts->value = rtst;
	rts->disabled = (rts->value == ZD1201_RTSMAX);
	rts->fixed = 1;

	return 0;
}
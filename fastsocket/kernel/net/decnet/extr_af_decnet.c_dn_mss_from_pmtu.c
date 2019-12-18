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
struct net_device {struct dn_dev* dn_ptr; } ;
struct dn_dev {scalar_t__ use_long; } ;

/* Variables and functions */
 int DN_MAX_NSP_DATA_HEADER ; 
 scalar_t__ LL_RESERVED_SPACE (struct net_device*) ; 

unsigned dn_mss_from_pmtu(struct net_device *dev, int mtu)
{
	unsigned mss = 230 - DN_MAX_NSP_DATA_HEADER;
	if (dev) {
		struct dn_dev *dn_db = dev->dn_ptr;
		mtu -= LL_RESERVED_SPACE(dev);
		if (dn_db->use_long)
			mtu -= 21;
		else
			mtu -= 6;
		mtu -= DN_MAX_NSP_DATA_HEADER;
	} else {
		/*
		 * 21 = long header, 16 = guess at MAC header length
		 */
		mtu -= (21 + DN_MAX_NSP_DATA_HEADER + 16);
	}
	if (mtu > mss)
		mss = mtu;
	return mss;
}
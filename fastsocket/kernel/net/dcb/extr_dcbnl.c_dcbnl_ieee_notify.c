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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_CAP_DCBX_VER_IEEE ; 
 int dcbnl_notify (struct net_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dcbnl_ieee_notify(struct net_device *dev, int event, int cmd,
		      u32 seq, u32 pid)
{
	return dcbnl_notify(dev, event, cmd, seq, pid, DCB_CAP_DCBX_VER_IEEE);
}
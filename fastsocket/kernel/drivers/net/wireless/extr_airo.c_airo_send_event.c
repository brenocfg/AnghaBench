#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sa_family; int /*<<< orphan*/  sa_data; } ;
struct TYPE_5__ {scalar_t__ flags; scalar_t__ length; } ;
union iwreq_data {TYPE_2__ ap_addr; TYPE_1__ data; } ;
struct net_device {struct airo_info* ml_priv; } ;
struct airo_info {int /*<<< orphan*/  sem; int /*<<< orphan*/  jobs; } ;
typedef  int /*<<< orphan*/  status_rid ;
struct TYPE_7__ {int /*<<< orphan*/ * bssid; } ;
typedef  TYPE_3__ StatusRid ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  JOB_EVENT ; 
 int /*<<< orphan*/  PC4500_readrid (struct airo_info*,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RID_STATUS ; 
 int /*<<< orphan*/  SIOCGIWAP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wireless_send_event (struct net_device*,int /*<<< orphan*/ ,union iwreq_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void airo_send_event(struct net_device *dev) {
	struct airo_info *ai = dev->ml_priv;
	union iwreq_data wrqu;
	StatusRid status_rid;

	clear_bit(JOB_EVENT, &ai->jobs);
	PC4500_readrid(ai, RID_STATUS, &status_rid, sizeof(status_rid), 0);
	up(&ai->sem);
	wrqu.data.length = 0;
	wrqu.data.flags = 0;
	memcpy(wrqu.ap_addr.sa_data, status_rid.bssid[0], ETH_ALEN);
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;

	/* Send event to user space */
	wireless_send_event(dev, SIOCGIWAP, &wrqu, NULL);
}
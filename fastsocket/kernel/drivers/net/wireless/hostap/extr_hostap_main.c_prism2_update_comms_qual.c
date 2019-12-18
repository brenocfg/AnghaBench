#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct hostap_interface {TYPE_2__* local; } ;
struct hfa384x_comms_quality {int /*<<< orphan*/  noise_level; int /*<<< orphan*/  signal_level; int /*<<< orphan*/  comm_qual; } ;
typedef  int /*<<< orphan*/  sq ;
typedef  void* s16 ;
struct TYPE_4__ {scalar_t__ sta_fw_ver; void* last_comms_qual_update; void* avg_noise; void* avg_signal; void* comms_qual; int /*<<< orphan*/  dev; TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_3__ {scalar_t__ (* get_rid ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfa384x_comms_quality*,int,int) ;} ;

/* Variables and functions */
 void* HFA384X_LEVEL_TO_dBm (void*) ; 
 int /*<<< orphan*/  HFA384X_RID_COMMSQUALITY ; 
 int /*<<< orphan*/  HFA384X_RID_DBMCOMMSQUALITY ; 
 scalar_t__ PRISM2_FW_VER (int,int,int) ; 
 void* jiffies ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfa384x_comms_quality*,int,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hfa384x_comms_quality*,int,int) ; 

int prism2_update_comms_qual(struct net_device *dev)
{
	struct hostap_interface *iface;
	local_info_t *local;
	int ret = 0;
	struct hfa384x_comms_quality sq;

	iface = netdev_priv(dev);
	local = iface->local;
	if (!local->sta_fw_ver)
		ret = -1;
	else if (local->sta_fw_ver >= PRISM2_FW_VER(1,3,1)) {
		if (local->func->get_rid(local->dev,
					 HFA384X_RID_DBMCOMMSQUALITY,
					 &sq, sizeof(sq), 1) >= 0) {
			local->comms_qual = (s16) le16_to_cpu(sq.comm_qual);
			local->avg_signal = (s16) le16_to_cpu(sq.signal_level);
			local->avg_noise = (s16) le16_to_cpu(sq.noise_level);
			local->last_comms_qual_update = jiffies;
		} else
			ret = -1;
	} else {
		if (local->func->get_rid(local->dev, HFA384X_RID_COMMSQUALITY,
					 &sq, sizeof(sq), 1) >= 0) {
			local->comms_qual = le16_to_cpu(sq.comm_qual);
			local->avg_signal = HFA384X_LEVEL_TO_dBm(
				le16_to_cpu(sq.signal_level));
			local->avg_noise = HFA384X_LEVEL_TO_dBm(
				le16_to_cpu(sq.noise_level));
			local->last_comms_qual_update = jiffies;
		} else
			ret = -1;
	}

	return ret;
}
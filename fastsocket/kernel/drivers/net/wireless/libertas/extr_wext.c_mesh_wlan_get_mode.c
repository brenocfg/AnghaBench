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
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_MODE_REPEAT ; 
 int /*<<< orphan*/  LBS_DEB_WEXT ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mesh_wlan_get_mode(struct net_device *dev,
		              struct iw_request_info *info, u32 * uwrq,
			      char *extra)
{
	lbs_deb_enter(LBS_DEB_WEXT);

	*uwrq = IW_MODE_REPEAT;

	lbs_deb_leave(LBS_DEB_WEXT);
	return 0;
}
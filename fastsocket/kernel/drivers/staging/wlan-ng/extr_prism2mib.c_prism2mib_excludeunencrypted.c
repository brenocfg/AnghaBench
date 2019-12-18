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
typedef  int /*<<< orphan*/  wlandevice_t ;
typedef  int /*<<< orphan*/  p80211msg_dot11req_mibset_t ;
typedef  int /*<<< orphan*/  mibrec_t ;
typedef  int /*<<< orphan*/  hfa384x_t ;

/* Variables and functions */
 int prism2mib_flag (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int prism2mib_excludeunencrypted(mibrec_t *mib,
					int isget,
					wlandevice_t *wlandev,
					hfa384x_t *hw,
					p80211msg_dot11req_mibset_t *msg,
					void *data)
{
	int result;

	result = prism2mib_flag(mib, isget, wlandev, hw, msg, data);

	return result;
}
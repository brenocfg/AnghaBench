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
struct iw_request_info {int dummy; } ;
struct iw_param {int value; } ;
typedef  int /*<<< orphan*/  netdevice_t ;

/* Variables and functions */
 int EFAULT ; 
 int p80211wext_giwrate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct iw_param*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int p80211wext_giwname(netdevice_t *dev,
			      struct iw_request_info *info,
			      char *name, char *extra)
{
	struct iw_param rate;
	int result;
	int err = 0;

	result = p80211wext_giwrate(dev, NULL, &rate, NULL);

	if (result) {
		err = -EFAULT;
		goto exit;
	}

	switch (rate.value) {
	case 1000000:
	case 2000000:
		strcpy(name, "IEEE 802.11-DS");
		break;
	case 5500000:
	case 11000000:
		strcpy(name, "IEEE 802.11-b");
		break;
	}
exit:
	return err;
}
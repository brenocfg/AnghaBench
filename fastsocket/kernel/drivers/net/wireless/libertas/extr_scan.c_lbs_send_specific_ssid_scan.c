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
typedef  scalar_t__ uint8_t ;
struct lbs_private {scalar_t__ surpriseremoved; scalar_t__ scan_ssid_len; int /*<<< orphan*/  scan_ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_SSID_BUF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LBS_DEB_SCAN ; 
 int /*<<< orphan*/  lbs_deb_enter_args (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_scan_networks (struct lbs_private*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  print_ssid (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  ssid_buf ; 

int lbs_send_specific_ssid_scan(struct lbs_private *priv, uint8_t *ssid,
				uint8_t ssid_len)
{
	DECLARE_SSID_BUF(ssid_buf);
	int ret = 0;

	lbs_deb_enter_args(LBS_DEB_SCAN, "SSID '%s'\n",
			   print_ssid(ssid_buf, ssid, ssid_len));

	if (!ssid_len)
		goto out;

	memcpy(priv->scan_ssid, ssid, ssid_len);
	priv->scan_ssid_len = ssid_len;

	lbs_scan_networks(priv, 1);
	if (priv->surpriseremoved) {
		ret = -1;
		goto out;
	}

out:
	lbs_deb_leave_args(LBS_DEB_SCAN, "ret %d", ret);
	return ret;
}
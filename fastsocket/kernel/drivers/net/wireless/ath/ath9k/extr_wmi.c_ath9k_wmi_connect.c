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
struct wmi {int ctrl_epid; struct htc_target* htc; } ;
struct htc_target {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; struct wmi* priv; } ;
struct htc_service_connreq {int /*<<< orphan*/  service_id; TYPE_1__ ep_callbacks; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;
typedef  int /*<<< orphan*/  connect ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_CONTROL_SVC ; 
 int /*<<< orphan*/  ath9k_wmi_ctrl_rx ; 
 int /*<<< orphan*/  ath9k_wmi_ctrl_tx ; 
 int htc_connect_service (struct htc_target*,struct htc_service_connreq*,int*) ; 
 int /*<<< orphan*/  memset (struct htc_service_connreq*,int /*<<< orphan*/ ,int) ; 

int ath9k_wmi_connect(struct htc_target *htc, struct wmi *wmi,
		      enum htc_endpoint_id *wmi_ctrl_epid)
{
	struct htc_service_connreq connect;
	int ret;

	wmi->htc = htc;

	memset(&connect, 0, sizeof(connect));

	connect.ep_callbacks.priv = wmi;
	connect.ep_callbacks.tx = ath9k_wmi_ctrl_tx;
	connect.ep_callbacks.rx = ath9k_wmi_ctrl_rx;
	connect.service_id = WMI_CONTROL_SVC;

	ret = htc_connect_service(htc, &connect, &wmi->ctrl_epid);
	if (ret)
		return ret;

	*wmi_ctrl_epid = wmi->ctrl_epid;

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wlp_wss {scalar_t__ state; scalar_t__ secure_status; } ;
struct wlp_uuid {int dummy; } ;
struct wlp_neighbor_e {TYPE_3__* uwb_dev; } ;
struct wlp {TYPE_2__* rc; } ;
struct uwb_dev_addr {int /*<<< orphan*/ * data; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {struct uwb_dev_addr dev_addr; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_5__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WLP_WSS_SECURE ; 
 scalar_t__ WLP_WSS_STATE_ENROLLED ; 
 scalar_t__ WLP_WSS_STATE_PART_ENROLLED ; 
 int WLP_WSS_UUID_STRSIZE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int wlp_d1d2_exchange (struct wlp*,struct wlp_neighbor_e*,struct wlp_wss*,struct wlp_uuid*) ; 
 int /*<<< orphan*/  wlp_wss_reset (struct wlp_wss*) ; 
 int /*<<< orphan*/  wlp_wss_uuid_print (char*,int,struct wlp_uuid*) ; 

int wlp_enroll_neighbor(struct wlp *wlp, struct wlp_neighbor_e *neighbor,
			struct wlp_wss *wss, struct wlp_uuid *wssid)
{
	int result = 0;
	struct device *dev = &wlp->rc->uwb_dev.dev;
	char buf[WLP_WSS_UUID_STRSIZE];
	struct uwb_dev_addr *dev_addr = &neighbor->uwb_dev->dev_addr;

	wlp_wss_uuid_print(buf, sizeof(buf), wssid);

	result =  wlp_d1d2_exchange(wlp, neighbor, wss, wssid);
	if (result < 0) {
		dev_err(dev, "WLP: D1/D2 message exchange for enrollment "
			"failed. result = %d \n", result);
		goto out;
	}
	if (wss->state != WLP_WSS_STATE_PART_ENROLLED) {
		dev_err(dev, "WLP: Unable to enroll into WSS %s using "
			"neighbor %02x:%02x. \n", buf,
			dev_addr->data[1], dev_addr->data[0]);
		result = -EINVAL;
		goto out;
	}
	if (wss->secure_status == WLP_WSS_SECURE) {
		dev_err(dev, "FIXME: need to complete secure enrollment.\n");
		result = -EINVAL;
		goto error;
	} else {
		wss->state = WLP_WSS_STATE_ENROLLED;
		dev_dbg(dev, "WLP: Success Enrollment into unsecure WSS "
			"%s using neighbor %02x:%02x. \n",
			buf, dev_addr->data[1], dev_addr->data[0]);
	}
out:
	return result;
error:
	wlp_wss_reset(wss);
	return result;
}
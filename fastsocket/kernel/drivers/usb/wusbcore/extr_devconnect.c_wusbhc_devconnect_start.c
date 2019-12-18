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
struct wusbhc {int trust_timeout; int /*<<< orphan*/  keep_alive_timer; struct wuie_host_info* wuie_host_info; int /*<<< orphan*/  chid; TYPE_1__* rsv; struct device* dev; } ;
struct TYPE_4__ {int bLength; int /*<<< orphan*/  bIEIdentifier; } ;
struct wuie_host_info {TYPE_2__ hdr; int /*<<< orphan*/  CHID; int /*<<< orphan*/  attributes; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int stream; } ;

/* Variables and functions */
 int CONFIG_HZ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WUIE_HI_CAP_ALL ; 
 int /*<<< orphan*/  WUIE_ID_HOST_INFO ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct wuie_host_info*) ; 
 struct wuie_host_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wusbd ; 
 int wusbhc_mmcie_set (struct wusbhc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

int wusbhc_devconnect_start(struct wusbhc *wusbhc)
{
	struct device *dev = wusbhc->dev;
	struct wuie_host_info *hi;
	int result;

	hi = kzalloc(sizeof(*hi), GFP_KERNEL);
	if (hi == NULL)
		return -ENOMEM;

	hi->hdr.bLength       = sizeof(*hi);
	hi->hdr.bIEIdentifier = WUIE_ID_HOST_INFO;
	hi->attributes        = cpu_to_le16((wusbhc->rsv->stream << 3) | WUIE_HI_CAP_ALL);
	hi->CHID              = wusbhc->chid;
	result = wusbhc_mmcie_set(wusbhc, 0, 0, &hi->hdr);
	if (result < 0) {
		dev_err(dev, "Cannot add Host Info MMCIE: %d\n", result);
		goto error_mmcie_set;
	}
	wusbhc->wuie_host_info = hi;

	queue_delayed_work(wusbd, &wusbhc->keep_alive_timer,
			   (wusbhc->trust_timeout*CONFIG_HZ)/1000/2);

	return 0;

error_mmcie_set:
	kfree(hi);
	return result;
}
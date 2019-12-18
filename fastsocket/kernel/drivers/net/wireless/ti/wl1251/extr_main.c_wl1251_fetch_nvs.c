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
struct wl1251 {int nvs_len; int /*<<< orphan*/  nvs; TYPE_1__* hw; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int EILSEQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WL1251_NVS_NAME ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 
 struct device* wiphy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_error (char*,...) ; 

__attribute__((used)) static int wl1251_fetch_nvs(struct wl1251 *wl)
{
	const struct firmware *fw;
	struct device *dev = wiphy_dev(wl->hw->wiphy);
	int ret;

	ret = request_firmware(&fw, WL1251_NVS_NAME, dev);

	if (ret < 0) {
		wl1251_error("could not get nvs file: %d", ret);
		return ret;
	}

	if (fw->size % 4) {
		wl1251_error("nvs size is not multiple of 32 bits: %zu",
			     fw->size);
		ret = -EILSEQ;
		goto out;
	}

	wl->nvs_len = fw->size;
	wl->nvs = kmemdup(fw->data, wl->nvs_len, GFP_KERNEL);

	if (!wl->nvs) {
		wl1251_error("could not allocate memory for the nvs file");
		ret = -ENOMEM;
		goto out;
	}

	ret = 0;

out:
	release_firmware(fw);

	return ret;
}
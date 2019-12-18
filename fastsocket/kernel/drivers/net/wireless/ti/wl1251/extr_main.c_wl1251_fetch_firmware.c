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
struct wl1251 {int fw_len; int /*<<< orphan*/  fw; TYPE_1__* hw; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int EILSEQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  WL1251_FW_NAME ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  vmalloc (int) ; 
 struct device* wiphy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_error (char*,...) ; 

__attribute__((used)) static int wl1251_fetch_firmware(struct wl1251 *wl)
{
	const struct firmware *fw;
	struct device *dev = wiphy_dev(wl->hw->wiphy);
	int ret;

	ret = request_firmware(&fw, WL1251_FW_NAME, dev);

	if (ret < 0) {
		wl1251_error("could not get firmware: %d", ret);
		return ret;
	}

	if (fw->size % 4) {
		wl1251_error("firmware size is not multiple of 32 bits: %zu",
			     fw->size);
		ret = -EILSEQ;
		goto out;
	}

	wl->fw_len = fw->size;
	wl->fw = vmalloc(wl->fw_len);

	if (!wl->fw) {
		wl1251_error("could not allocate memory for the firmware");
		ret = -ENOMEM;
		goto out;
	}

	memcpy(wl->fw, fw->data, wl->fw_len);

	ret = 0;

out:
	release_firmware(fw);

	return ret;
}
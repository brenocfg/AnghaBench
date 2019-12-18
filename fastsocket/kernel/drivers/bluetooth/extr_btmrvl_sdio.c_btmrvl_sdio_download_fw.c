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
struct btmrvl_sdio_card {int /*<<< orphan*/  func; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int MAX_POLL_TRIES ; 
 scalar_t__ btmrvl_sdio_download_fw_w_helper (struct btmrvl_sdio_card*) ; 
 int btmrvl_sdio_download_helper (struct btmrvl_sdio_card*) ; 
 scalar_t__ btmrvl_sdio_verify_fw_download (struct btmrvl_sdio_card*,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btmrvl_sdio_download_fw(struct btmrvl_sdio_card *card)
{
	int ret = 0;

	if (!card || !card->func) {
		BT_ERR("card or function is NULL!");
		return -EINVAL;
	}
	sdio_claim_host(card->func);

	if (!btmrvl_sdio_verify_fw_download(card, 1)) {
		BT_DBG("Firmware already downloaded!");
		goto done;
	}

	ret = btmrvl_sdio_download_helper(card);
	if (ret) {
		BT_ERR("Failed to download helper!");
		ret = -EIO;
		goto done;
	}

	if (btmrvl_sdio_download_fw_w_helper(card)) {
		BT_ERR("Failed to download firmware!");
		ret = -EIO;
		goto done;
	}

	if (btmrvl_sdio_verify_fw_download(card, MAX_POLL_TRIES)) {
		BT_ERR("FW failed to be active in time!");
		ret = -ETIMEDOUT;
		goto done;
	}

done:
	sdio_release_host(card->func);

	return ret;
}
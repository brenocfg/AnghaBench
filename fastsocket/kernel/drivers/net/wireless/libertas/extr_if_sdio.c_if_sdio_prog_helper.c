#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct if_sdio_card {TYPE_1__* func; int /*<<< orphan*/  ioport; int /*<<< orphan*/  helper; } ;
struct firmware {int* data; size_t size; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long HZ ; 
 int IF_SDIO_DL_RDY ; 
 int IF_SDIO_IO_RDY ; 
 scalar_t__ IF_SDIO_RD_BASE ; 
 scalar_t__ IF_SDIO_STATUS ; 
 int /*<<< orphan*/  LBS_DEB_SDIO ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (size_t,size_t) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_1__*) ; 
 int sdio_readb (TYPE_1__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_1__*) ; 
 int sdio_set_block_size (TYPE_1__*,int) ; 
 int sdio_writesb (TYPE_1__*,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int if_sdio_prog_helper(struct if_sdio_card *card)
{
	int ret;
	u8 status;
	const struct firmware *fw;
	unsigned long timeout;
	u8 *chunk_buffer;
	u32 chunk_size;
	const u8 *firmware;
	size_t size;

	lbs_deb_enter(LBS_DEB_SDIO);

	ret = request_firmware(&fw, card->helper, &card->func->dev);
	if (ret) {
		lbs_pr_err("can't load helper firmware\n");
		goto out;
	}

	chunk_buffer = kzalloc(64, GFP_KERNEL);
	if (!chunk_buffer) {
		ret = -ENOMEM;
		goto release_fw;
	}

	sdio_claim_host(card->func);

	ret = sdio_set_block_size(card->func, 32);
	if (ret)
		goto release;

	firmware = fw->data;
	size = fw->size;

	while (size) {
		timeout = jiffies + HZ;
		while (1) {
			status = sdio_readb(card->func, IF_SDIO_STATUS, &ret);
			if (ret)
				goto release;
			if ((status & IF_SDIO_IO_RDY) &&
					(status & IF_SDIO_DL_RDY))
				break;
			if (time_after(jiffies, timeout)) {
				ret = -ETIMEDOUT;
				goto release;
			}
			mdelay(1);
		}

		chunk_size = min(size, (size_t)60);

		*((__le32*)chunk_buffer) = cpu_to_le32(chunk_size);
		memcpy(chunk_buffer + 4, firmware, chunk_size);
/*
		lbs_deb_sdio("sending %d bytes chunk\n", chunk_size);
*/
		ret = sdio_writesb(card->func, card->ioport,
				chunk_buffer, 64);
		if (ret)
			goto release;

		firmware += chunk_size;
		size -= chunk_size;
	}

	/* an empty block marks the end of the transfer */
	memset(chunk_buffer, 0, 4);
	ret = sdio_writesb(card->func, card->ioport, chunk_buffer, 64);
	if (ret)
		goto release;

	lbs_deb_sdio("waiting for helper to boot...\n");

	/* wait for the helper to boot by looking at the size register */
	timeout = jiffies + HZ;
	while (1) {
		u16 req_size;

		req_size = sdio_readb(card->func, IF_SDIO_RD_BASE, &ret);
		if (ret)
			goto release;

		req_size |= sdio_readb(card->func, IF_SDIO_RD_BASE + 1, &ret) << 8;
		if (ret)
			goto release;

		if (req_size != 0)
			break;

		if (time_after(jiffies, timeout)) {
			ret = -ETIMEDOUT;
			goto release;
		}

		msleep(10);
	}

	ret = 0;

release:
	sdio_release_host(card->func);
	kfree(chunk_buffer);
release_fw:
	release_firmware(fw);

out:
	if (ret)
		lbs_pr_err("failed to load helper firmware\n");

	lbs_deb_leave_args(LBS_DEB_SDIO, "ret %d", ret);

	return ret;
}
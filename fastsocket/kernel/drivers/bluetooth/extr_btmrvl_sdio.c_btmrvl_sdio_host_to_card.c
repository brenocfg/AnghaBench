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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct btmrvl_sdio_card {int /*<<< orphan*/  func; int /*<<< orphan*/  ioport; } ;
struct TYPE_2__ {int tx_dnld_rdy; struct btmrvl_sdio_card* card; } ;
struct btmrvl_private {TYPE_1__ btmrvl_dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN_ADDR (void*,int) ; 
 int ALIGN_SZ (int,int) ; 
 int BTSDIO_DMA_ALIGN ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_WRITE_IOMEM_RETRY ; 
 int SDIO_BLOCK_SIZE ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int sdio_writesb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int btmrvl_sdio_host_to_card(struct btmrvl_private *priv,
				u8 *payload, u16 nb)
{
	struct btmrvl_sdio_card *card = priv->btmrvl_dev.card;
	int ret = 0;
	int buf_block_len;
	int blksz;
	int i = 0;
	u8 *buf = NULL;
	void *tmpbuf = NULL;
	int tmpbufsz;

	if (!card || !card->func) {
		BT_ERR("card or function is NULL!");
		return -EINVAL;
	}

	buf = payload;
	if ((unsigned long) payload & (BTSDIO_DMA_ALIGN - 1)) {
		tmpbufsz = ALIGN_SZ(nb, BTSDIO_DMA_ALIGN);
		tmpbuf = kzalloc(tmpbufsz, GFP_KERNEL);
		if (!tmpbuf)
			return -ENOMEM;
		buf = (u8 *) ALIGN_ADDR(tmpbuf, BTSDIO_DMA_ALIGN);
		memcpy(buf, payload, nb);
	}

	blksz = SDIO_BLOCK_SIZE;
	buf_block_len = (nb + blksz - 1) / blksz;

	sdio_claim_host(card->func);

	do {
		/* Transfer data to card */
		ret = sdio_writesb(card->func, card->ioport, buf,
				   buf_block_len * blksz);
		if (ret < 0) {
			i++;
			BT_ERR("i=%d writesb failed: %d", i, ret);
			print_hex_dump_bytes("", DUMP_PREFIX_OFFSET,
						payload, nb);
			ret = -EIO;
			if (i > MAX_WRITE_IOMEM_RETRY)
				goto exit;
		}
	} while (ret);

	priv->btmrvl_dev.tx_dnld_rdy = false;

exit:
	sdio_release_host(card->func);

	return ret;
}
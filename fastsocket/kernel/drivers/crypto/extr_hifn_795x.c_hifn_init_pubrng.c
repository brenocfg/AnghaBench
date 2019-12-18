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
struct hifn_device {int dmareg; int /*<<< orphan*/  rngtime; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_1_DMA_IER ; 
 int /*<<< orphan*/  HIFN_1_PUB_IEN ; 
 int /*<<< orphan*/  HIFN_1_PUB_RESET ; 
 int /*<<< orphan*/  HIFN_1_RNG_CONFIG ; 
 int /*<<< orphan*/  HIFN_1_RNG_DATA ; 
 int HIFN_DMAIER_PUBDONE ; 
 int HIFN_PUBIEN_DONE ; 
 int HIFN_PUBRST_RESET ; 
 int HIFN_RNGCFG_ENA ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int hifn_read_1 (struct hifn_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hifn_write_1 (struct hifn_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int hifn_init_pubrng(struct hifn_device *dev)
{
	int i;

	hifn_write_1(dev, HIFN_1_PUB_RESET, hifn_read_1(dev, HIFN_1_PUB_RESET) |
			HIFN_PUBRST_RESET);

	for (i=100; i > 0; --i) {
		mdelay(1);

		if ((hifn_read_1(dev, HIFN_1_PUB_RESET) & HIFN_PUBRST_RESET) == 0)
			break;
	}

	if (!i)
		dprintk("Chip %s: Failed to initialise public key engine.\n",
				dev->name);
	else {
		hifn_write_1(dev, HIFN_1_PUB_IEN, HIFN_PUBIEN_DONE);
		dev->dmareg |= HIFN_DMAIER_PUBDONE;
		hifn_write_1(dev, HIFN_1_DMA_IER, dev->dmareg);

		dprintk("Chip %s: Public key engine has been sucessfully "
				"initialised.\n", dev->name);
	}

	/*
	 * Enable RNG engine.
	 */

	hifn_write_1(dev, HIFN_1_RNG_CONFIG,
			hifn_read_1(dev, HIFN_1_RNG_CONFIG) | HIFN_RNGCFG_ENA);
	dprintk("Chip %s: RNG engine has been successfully initialised.\n",
			dev->name);

#ifdef CONFIG_CRYPTO_DEV_HIFN_795X_RNG
	/* First value must be discarded */
	hifn_read_1(dev, HIFN_1_RNG_DATA);
	dev->rngtime = ktime_get();
#endif
	return 0;
}
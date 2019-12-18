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
struct sh_keysc_info {size_t mode; int* keycodes; scalar_t__ kycr2_delay; scalar_t__ delay; } ;
struct sh_keysc_priv {unsigned long last_keys; int /*<<< orphan*/  input; scalar_t__ iomem_base; struct sh_keysc_info pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int keyout; int keyin; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned char KYCR2_IRQ_DISABLED ; 
 unsigned char KYCR2_IRQ_LEVEL ; 
 scalar_t__ KYCR2_OFFS ; 
 scalar_t__ KYINDR_OFFS ; 
 scalar_t__ KYOUTDR_OFFS ; 
 int SH_KEYSC_MAXKEYS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (unsigned char,scalar_t__) ; 
 struct sh_keysc_priv* platform_get_drvdata (struct platform_device*) ; 
 TYPE_1__* sh_keysc_mode ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static irqreturn_t sh_keysc_isr(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;
	struct sh_keysc_priv *priv = platform_get_drvdata(pdev);
	struct sh_keysc_info *pdata = &priv->pdata;
	unsigned long keys, keys1, keys0, mask;
	unsigned char keyin_set, tmp;
	int i, k;

	dev_dbg(&pdev->dev, "isr!\n");

	keys1 = ~0;
	keys0 = 0;

	do {
		keys = 0;
		keyin_set = 0;

		iowrite16(KYCR2_IRQ_DISABLED, priv->iomem_base + KYCR2_OFFS);

		for (i = 0; i < sh_keysc_mode[pdata->mode].keyout; i++) {
			iowrite16(0xfff ^ (3 << (i * 2)),
				  priv->iomem_base + KYOUTDR_OFFS);
			udelay(pdata->delay);
			tmp = ioread16(priv->iomem_base + KYINDR_OFFS);
			keys |= tmp << (sh_keysc_mode[pdata->mode].keyin * i);
			tmp ^= (1 << sh_keysc_mode[pdata->mode].keyin) - 1;
			keyin_set |= tmp;
		}

		iowrite16(0, priv->iomem_base + KYOUTDR_OFFS);
		iowrite16(KYCR2_IRQ_LEVEL | (keyin_set << 8),
			  priv->iomem_base + KYCR2_OFFS);

		if (pdata->kycr2_delay)
			udelay(pdata->kycr2_delay);

		keys ^= ~0;
		keys &= (1 << (sh_keysc_mode[pdata->mode].keyin *
			       sh_keysc_mode[pdata->mode].keyout)) - 1;
		keys1 &= keys;
		keys0 |= keys;

		dev_dbg(&pdev->dev, "keys 0x%08lx\n", keys);

	} while (ioread16(priv->iomem_base + KYCR2_OFFS) & 0x01);

	dev_dbg(&pdev->dev, "last_keys 0x%08lx keys0 0x%08lx keys1 0x%08lx\n",
		priv->last_keys, keys0, keys1);

	for (i = 0; i < SH_KEYSC_MAXKEYS; i++) {
		k = pdata->keycodes[i];
		if (!k)
			continue;

		mask = 1 << i;

		if (!((priv->last_keys ^ keys0) & mask))
			continue;

		if ((keys1 | keys0) & mask) {
			input_event(priv->input, EV_KEY, k, 1);
			priv->last_keys |= mask;
		}

		if (!(keys1 & mask)) {
			input_event(priv->input, EV_KEY, k, 0);
			priv->last_keys &= ~mask;
		}

	}
	input_sync(priv->input);

	return IRQ_HANDLED;
}
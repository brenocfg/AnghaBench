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
struct p54s_priv {int /*<<< orphan*/  firmware; TYPE_1__* spi; } ;
struct ieee80211_hw {struct p54s_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int p54_parse_firmware (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int request_firmware (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p54spi_request_firmware(struct ieee80211_hw *dev)
{
	struct p54s_priv *priv = dev->priv;
	int ret;

	/* FIXME: should driver use it's own struct device? */
	ret = request_firmware(&priv->firmware, "3826.arm", &priv->spi->dev);

	if (ret < 0) {
		dev_err(&priv->spi->dev, "request_firmware() failed: %d", ret);
		return ret;
	}

	ret = p54_parse_firmware(dev, priv->firmware);
	if (ret) {
		release_firmware(priv->firmware);
		return ret;
	}

	return 0;
}
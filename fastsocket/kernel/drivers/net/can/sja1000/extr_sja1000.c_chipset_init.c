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
struct sja1000_priv {int cdr; int ocr; int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ,int) ;} ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int CDR_PELICAN ; 
 int OCR_MODE_NORMAL ; 
 int /*<<< orphan*/  REG_ACCC0 ; 
 int /*<<< orphan*/  REG_ACCC1 ; 
 int /*<<< orphan*/  REG_ACCC2 ; 
 int /*<<< orphan*/  REG_ACCC3 ; 
 int /*<<< orphan*/  REG_ACCM0 ; 
 int /*<<< orphan*/  REG_ACCM1 ; 
 int /*<<< orphan*/  REG_ACCM2 ; 
 int /*<<< orphan*/  REG_ACCM3 ; 
 int /*<<< orphan*/  REG_CDR ; 
 int /*<<< orphan*/  REG_OCR ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct sja1000_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void chipset_init(struct net_device *dev)
{
	struct sja1000_priv *priv = netdev_priv(dev);

	/* set clock divider and output control register */
	priv->write_reg(priv, REG_CDR, priv->cdr | CDR_PELICAN);

	/* set acceptance filter (accept all) */
	priv->write_reg(priv, REG_ACCC0, 0x00);
	priv->write_reg(priv, REG_ACCC1, 0x00);
	priv->write_reg(priv, REG_ACCC2, 0x00);
	priv->write_reg(priv, REG_ACCC3, 0x00);

	priv->write_reg(priv, REG_ACCM0, 0xFF);
	priv->write_reg(priv, REG_ACCM1, 0xFF);
	priv->write_reg(priv, REG_ACCM2, 0xFF);
	priv->write_reg(priv, REG_ACCM3, 0xFF);

	priv->write_reg(priv, REG_OCR, priv->ocr | OCR_MODE_NORMAL);
}
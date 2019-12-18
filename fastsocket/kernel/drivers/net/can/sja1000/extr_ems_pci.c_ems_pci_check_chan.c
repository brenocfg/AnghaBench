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
struct sja1000_priv {unsigned char (* read_reg ) (struct sja1000_priv const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_reg ) (struct sja1000_priv const*,int /*<<< orphan*/ ,unsigned char) ;} ;

/* Variables and functions */
 unsigned char CDR_PELICAN ; 
 int /*<<< orphan*/  REG_CDR ; 
 int /*<<< orphan*/  REG_MOD ; 
 int /*<<< orphan*/  stub1 (struct sja1000_priv const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct sja1000_priv const*,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char stub3 (struct sja1000_priv const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ems_pci_check_chan(const struct sja1000_priv *priv)
{
	unsigned char res;

	/* Make sure SJA1000 is in reset mode */
	priv->write_reg(priv, REG_MOD, 1);

	priv->write_reg(priv, REG_CDR, CDR_PELICAN);

	/* read reset-values */
	res = priv->read_reg(priv, REG_CDR);

	if (res == CDR_PELICAN)
		return 1;

	return 0;
}
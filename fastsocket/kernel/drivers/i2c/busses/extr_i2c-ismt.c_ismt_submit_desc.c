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
typedef  int uint ;
struct ismt_priv {int head; scalar_t__ smba; } ;

/* Variables and functions */
 int ISMT_DESC_ENTRIES ; 
 int ISMT_MCTRL_FMHP ; 
 int ISMT_MCTRL_SS ; 
 scalar_t__ ISMT_MSTR_MCTRL ; 
 int /*<<< orphan*/  ismt_desc_dump (struct ismt_priv*) ; 
 int /*<<< orphan*/  ismt_gen_reg_dump (struct ismt_priv*) ; 
 int /*<<< orphan*/  ismt_mstr_reg_dump (struct ismt_priv*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ismt_submit_desc(struct ismt_priv *priv)
{
	uint fmhp;
	uint val;

	ismt_desc_dump(priv);
	ismt_gen_reg_dump(priv);
	ismt_mstr_reg_dump(priv);

	/* Set the FMHP (Firmware Master Head Pointer)*/
	fmhp = ((priv->head + 1) % ISMT_DESC_ENTRIES) << 16;
	val = readl(priv->smba + ISMT_MSTR_MCTRL);
	writel((val & ~ISMT_MCTRL_FMHP) | fmhp,
	       priv->smba + ISMT_MSTR_MCTRL);

	/* Set the start bit */
	val = readl(priv->smba + ISMT_MSTR_MCTRL);
	writel(val | ISMT_MCTRL_SS,
	       priv->smba + ISMT_MSTR_MCTRL);
}
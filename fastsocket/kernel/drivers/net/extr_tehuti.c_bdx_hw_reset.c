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
typedef  int u32 ;
struct bdx_priv {scalar_t__ port; } ;

/* Variables and functions */
 int CLKPLL_LKD ; 
 int CLKPLL_SFTRST ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int READ_REG (struct bdx_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regCLKPLL ; 
 int /*<<< orphan*/  regRXD_CFG0_0 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int bdx_hw_reset(struct bdx_priv *priv)
{
	u32 val, i;
	ENTER;

	if (priv->port == 0) {
		/* reset sequences: read, write 1, read, write 0 */
		val = READ_REG(priv, regCLKPLL);
		WRITE_REG(priv, regCLKPLL, (val | CLKPLL_SFTRST) + 0x8);
		udelay(50);
		val = READ_REG(priv, regCLKPLL);
		WRITE_REG(priv, regCLKPLL, val & ~CLKPLL_SFTRST);
	}
	/* check that the PLLs are locked and reset ended */
	for (i = 0; i < 70; i++, mdelay(10))
		if ((READ_REG(priv, regCLKPLL) & CLKPLL_LKD) == CLKPLL_LKD) {
			/* do any PCI-E read transaction */
			READ_REG(priv, regRXD_CFG0_0);
			return 0;
		}
	ERR("tehuti: HW reset failed\n");
	return 1;		/* failure */
}
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
typedef  int u32 ;
struct i2c_au1550_data {scalar_t__ psc_base; } ;
struct TYPE_2__ {int psc_smbcfg; int psc_smbstat; int psc_smbtmr; int /*<<< orphan*/  psc_ctrl; int /*<<< orphan*/  psc_smbmsk; int /*<<< orphan*/  psc_sel; } ;
typedef  TYPE_1__ psc_smb_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_CTRL_DISABLE ; 
 int /*<<< orphan*/  PSC_CTRL_ENABLE ; 
 int /*<<< orphan*/  PSC_CTRL_SUSPEND ; 
 int /*<<< orphan*/  PSC_SEL_PS_SMBUSMODE ; 
 int PSC_SMBCFG_DD_DISABLE ; 
 int PSC_SMBCFG_DE_ENABLE ; 
 int /*<<< orphan*/  PSC_SMBCFG_DIV8 ; 
 int PSC_SMBCFG_RT_FIFO8 ; 
 int PSC_SMBCFG_SET_DIV (int /*<<< orphan*/ ) ; 
 int PSC_SMBCFG_TT_FIFO8 ; 
 int /*<<< orphan*/  PSC_SMBMSK_ALLMASK ; 
 int PSC_SMBSTAT_SR ; 
 int PSC_SMBTMR_SET_CH (int) ; 
 int PSC_SMBTMR_SET_CL (int) ; 
 int PSC_SMBTMR_SET_PS (int) ; 
 int PSC_SMBTMR_SET_PU (int) ; 
 int PSC_SMBTMR_SET_SH (int) ; 
 int PSC_SMBTMR_SET_SU (int) ; 
 int PSC_SMBTMR_SET_TH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sync () ; 

__attribute__((used)) static void i2c_au1550_setup(struct i2c_au1550_data *priv)
{
	volatile psc_smb_t *sp = (volatile psc_smb_t *)priv->psc_base;
	u32 stat;

	sp->psc_ctrl = PSC_CTRL_DISABLE;
	au_sync();
	sp->psc_sel = PSC_SEL_PS_SMBUSMODE;
	sp->psc_smbcfg = 0;
	au_sync();
	sp->psc_ctrl = PSC_CTRL_ENABLE;
	au_sync();
	do {
		stat = sp->psc_smbstat;
		au_sync();
	} while ((stat & PSC_SMBSTAT_SR) == 0);

	sp->psc_smbcfg = (PSC_SMBCFG_RT_FIFO8 | PSC_SMBCFG_TT_FIFO8 |
				PSC_SMBCFG_DD_DISABLE);

	/* Divide by 8 to get a 6.25 MHz clock.  The later protocol
	 * timings are based on this clock.
	 */
	sp->psc_smbcfg |= PSC_SMBCFG_SET_DIV(PSC_SMBCFG_DIV8);
	sp->psc_smbmsk = PSC_SMBMSK_ALLMASK;
	au_sync();

	/* Set the protocol timer values.  See Table 71 in the
	 * Au1550 Data Book for standard timing values.
	 */
	sp->psc_smbtmr = PSC_SMBTMR_SET_TH(0) | PSC_SMBTMR_SET_PS(15) | \
		PSC_SMBTMR_SET_PU(15) | PSC_SMBTMR_SET_SH(15) | \
		PSC_SMBTMR_SET_SU(15) | PSC_SMBTMR_SET_CL(15) | \
		PSC_SMBTMR_SET_CH(15);
	au_sync();

	sp->psc_smbcfg |= PSC_SMBCFG_DE_ENABLE;
	do {
		stat = sp->psc_smbstat;
		au_sync();
	} while ((stat & PSC_SMBSTAT_SR) == 0);

	sp->psc_ctrl = PSC_CTRL_SUSPEND;
	au_sync();
}
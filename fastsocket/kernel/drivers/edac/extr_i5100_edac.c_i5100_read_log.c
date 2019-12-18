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
typedef  unsigned int u32 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {struct pci_dev* ch0mm; struct pci_dev* ch1mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  I5100_NRECMEMA ; 
 int /*<<< orphan*/  I5100_NRECMEMB ; 
 int /*<<< orphan*/  I5100_RECMEMA ; 
 int /*<<< orphan*/  I5100_RECMEMB ; 
 int /*<<< orphan*/  I5100_REDMEMA ; 
 int /*<<< orphan*/  I5100_REDMEMB ; 
 int /*<<< orphan*/  I5100_VALIDLOG ; 
 char* i5100_err_msg (unsigned int) ; 
 int /*<<< orphan*/  i5100_handle_ce (struct mem_ctl_info*,int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,char const*) ; 
 int /*<<< orphan*/  i5100_handle_ue (struct mem_ctl_info*,int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,char const*) ; 
 unsigned int i5100_nrecmema_bank (unsigned int) ; 
 unsigned int i5100_nrecmema_merr (unsigned int) ; 
 unsigned int i5100_nrecmema_rank (unsigned int) ; 
 unsigned int i5100_nrecmemb_cas (unsigned int) ; 
 unsigned int i5100_nrecmemb_ras (unsigned int) ; 
 unsigned int i5100_recmema_bank (unsigned int) ; 
 unsigned int i5100_recmema_merr (unsigned int) ; 
 unsigned int i5100_recmema_rank (unsigned int) ; 
 unsigned int i5100_recmemb_cas (unsigned int) ; 
 unsigned int i5100_recmemb_ras (unsigned int) ; 
 unsigned int i5100_redmemb_ecc_locator (unsigned int) ; 
 scalar_t__ i5100_validlog_nrecmemvalid (unsigned int) ; 
 scalar_t__ i5100_validlog_recmemvalid (unsigned int) ; 
 scalar_t__ i5100_validlog_redmemvalid (unsigned int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void i5100_read_log(struct mem_ctl_info *mci, int ctlr,
			   u32 ferr, u32 nerr)
{
	struct i5100_priv *priv = mci->pvt_info;
	struct pci_dev *pdev = (ctlr) ? priv->ch1mm : priv->ch0mm;
	u32 dw;
	u32 dw2;
	unsigned syndrome = 0;
	unsigned ecc_loc = 0;
	unsigned merr;
	unsigned bank;
	unsigned rank;
	unsigned cas;
	unsigned ras;

	pci_read_config_dword(pdev, I5100_VALIDLOG, &dw);

	if (i5100_validlog_redmemvalid(dw)) {
		pci_read_config_dword(pdev, I5100_REDMEMA, &dw2);
		syndrome = dw2;
		pci_read_config_dword(pdev, I5100_REDMEMB, &dw2);
		ecc_loc = i5100_redmemb_ecc_locator(dw2);
	}

	if (i5100_validlog_recmemvalid(dw)) {
		const char *msg;

		pci_read_config_dword(pdev, I5100_RECMEMA, &dw2);
		merr = i5100_recmema_merr(dw2);
		bank = i5100_recmema_bank(dw2);
		rank = i5100_recmema_rank(dw2);

		pci_read_config_dword(pdev, I5100_RECMEMB, &dw2);
		cas = i5100_recmemb_cas(dw2);
		ras = i5100_recmemb_ras(dw2);

		/* FIXME:  not really sure if this is what merr is...
		 */
		if (!merr)
			msg = i5100_err_msg(ferr);
		else
			msg = i5100_err_msg(nerr);

		i5100_handle_ce(mci, ctlr, bank, rank, syndrome, cas, ras, msg);
	}

	if (i5100_validlog_nrecmemvalid(dw)) {
		const char *msg;

		pci_read_config_dword(pdev, I5100_NRECMEMA, &dw2);
		merr = i5100_nrecmema_merr(dw2);
		bank = i5100_nrecmema_bank(dw2);
		rank = i5100_nrecmema_rank(dw2);

		pci_read_config_dword(pdev, I5100_NRECMEMB, &dw2);
		cas = i5100_nrecmemb_cas(dw2);
		ras = i5100_nrecmemb_ras(dw2);

		/* FIXME:  not really sure if this is what merr is...
		 */
		if (!merr)
			msg = i5100_err_msg(ferr);
		else
			msg = i5100_err_msg(nerr);

		i5100_handle_ue(mci, ctlr, bank, rank, syndrome, cas, ras, msg);
	}

	pci_write_config_dword(pdev, I5100_VALIDLOG, dw);
}
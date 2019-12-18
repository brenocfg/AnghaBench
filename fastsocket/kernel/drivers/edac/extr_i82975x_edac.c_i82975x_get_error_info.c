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
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  dev; } ;
struct i82975x_error_info {int errsts; int errsts2; int /*<<< orphan*/  derrsyn; int /*<<< orphan*/  des; int /*<<< orphan*/  xeap; int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I82975X_DERRSYN ; 
 int /*<<< orphan*/  I82975X_DES ; 
 int /*<<< orphan*/  I82975X_EAP ; 
 int /*<<< orphan*/  I82975X_ERRSTS ; 
 int /*<<< orphan*/  I82975X_XEAP ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_bits16 (struct pci_dev*,int /*<<< orphan*/ ,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i82975x_get_error_info(struct mem_ctl_info *mci,
		struct i82975x_error_info *info)
{
	struct pci_dev *pdev;

	pdev = to_pci_dev(mci->dev);

	/*
	 * This is a mess because there is no atomic way to read all the
	 * registers at once and the registers can transition from CE being
	 * overwritten by UE.
	 */
	pci_read_config_word(pdev, I82975X_ERRSTS, &info->errsts);
	pci_read_config_dword(pdev, I82975X_EAP, &info->eap);
	pci_read_config_byte(pdev, I82975X_XEAP, &info->xeap);
	pci_read_config_byte(pdev, I82975X_DES, &info->des);
	pci_read_config_byte(pdev, I82975X_DERRSYN, &info->derrsyn);
	pci_read_config_word(pdev, I82975X_ERRSTS, &info->errsts2);

	pci_write_bits16(pdev, I82975X_ERRSTS, 0x0003, 0x0003);

	/*
	 * If the error is the same then we can for both reads then
	 * the first set of reads is valid.  If there is a change then
	 * there is a CE no info and the second set of reads is valid
	 * and should be UE info.
	 */
	if (!(info->errsts2 & 0x0003))
		return;

	if ((info->errsts ^ info->errsts2) & 0x0003) {
		pci_read_config_dword(pdev, I82975X_EAP, &info->eap);
		pci_read_config_byte(pdev, I82975X_XEAP, &info->xeap);
		pci_read_config_byte(pdev, I82975X_DES, &info->des);
		pci_read_config_byte(pdev, I82975X_DERRSYN,
				&info->derrsyn);
	}
}
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
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCDEBUG_ERRCNT1 ; 
 int MCDEBUG_ERRCNT1_SBE_CNT_OVRFLO ; 
 int /*<<< orphan*/  MCDEBUG_ERRSTA ; 
 int MCDEBUG_ERRSTA_MBE_STATUS ; 
 int MCDEBUG_ERRSTA_RFL_STATUS ; 
 int MCDEBUG_ERRSTA_SBE_STATUS ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pasemi_edac_get_error_info(struct mem_ctl_info *mci)
{
	struct pci_dev *pdev = to_pci_dev(mci->dev);
	u32 tmp;

	pci_read_config_dword(pdev, MCDEBUG_ERRSTA,
			      &tmp);

	tmp &= (MCDEBUG_ERRSTA_RFL_STATUS | MCDEBUG_ERRSTA_MBE_STATUS
		| MCDEBUG_ERRSTA_SBE_STATUS);

	if (tmp) {
		if (tmp & MCDEBUG_ERRSTA_SBE_STATUS)
			pci_write_config_dword(pdev, MCDEBUG_ERRCNT1,
					       MCDEBUG_ERRCNT1_SBE_CNT_OVRFLO);
		pci_write_config_dword(pdev, MCDEBUG_ERRSTA, tmp);
	}

	return tmp;
}
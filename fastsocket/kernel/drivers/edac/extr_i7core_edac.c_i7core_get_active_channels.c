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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIMM_PRESENT (int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  MC_CONTROL ; 
 int /*<<< orphan*/  MC_DOD_CH_DIMM0 ; 
 int /*<<< orphan*/  MC_DOD_CH_DIMM1 ; 
 int /*<<< orphan*/  MC_DOD_CH_DIMM2 ; 
 int /*<<< orphan*/  MC_STATUS ; 
 int NUM_CHANS ; 
 int /*<<< orphan*/  debugf0 (char*,int /*<<< orphan*/  const,unsigned int) ; 
 struct pci_dev* get_pdev_slot_func (int /*<<< orphan*/  const,int,int) ; 
 int /*<<< orphan*/  i7core_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const,...) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int i7core_get_active_channels(const u8 socket, unsigned *channels,
				      unsigned *csrows)
{
	struct pci_dev *pdev = NULL;
	int i, j;
	u32 status, control;

	*channels = 0;
	*csrows = 0;

	pdev = get_pdev_slot_func(socket, 3, 0);
	if (!pdev) {
		i7core_printk(KERN_ERR, "Couldn't find socket %d fn 3.0!!!\n",
			      socket);
		return -ENODEV;
	}

	/* Device 3 function 0 reads */
	pci_read_config_dword(pdev, MC_STATUS, &status);
	pci_read_config_dword(pdev, MC_CONTROL, &control);

	for (i = 0; i < NUM_CHANS; i++) {
		u32 dimm_dod[3];
		/* Check if the channel is active */
		if (!(control & (1 << (8 + i))))
			continue;

		/* Check if the channel is disabled */
		if (status & (1 << i))
			continue;

		pdev = get_pdev_slot_func(socket, i + 4, 1);
		if (!pdev) {
			i7core_printk(KERN_ERR, "Couldn't find socket %d "
						"fn %d.%d!!!\n",
						socket, i + 4, 1);
			return -ENODEV;
		}
		/* Devices 4-6 function 1 */
		pci_read_config_dword(pdev,
				MC_DOD_CH_DIMM0, &dimm_dod[0]);
		pci_read_config_dword(pdev,
				MC_DOD_CH_DIMM1, &dimm_dod[1]);
		pci_read_config_dword(pdev,
				MC_DOD_CH_DIMM2, &dimm_dod[2]);

		(*channels)++;

		for (j = 0; j < 3; j++) {
			if (!DIMM_PRESENT(dimm_dod[j]))
				continue;
			(*csrows)++;
		}
	}

	debugf0("Number of active channels on socket %d: %d\n",
		socket, *channels);

	return 0;
}
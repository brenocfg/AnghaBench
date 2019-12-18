#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pci_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ scrubval; scalar_t__ bandwidth; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  SCRCTRL ; 
 int /*<<< orphan*/  pci_write_bits32 (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 TYPE_1__* scrubrates ; 

__attribute__((used)) static int __amd64_set_scrub_rate(struct pci_dev *ctl, u32 new_bw, u32 min_rate)
{
	u32 scrubval;
	int i;

	/*
	 * map the configured rate (new_bw) to a value specific to the AMD64
	 * memory controller and apply to register. Search for the first
	 * bandwidth entry that is greater or equal than the setting requested
	 * and program that. If at last entry, turn off DRAM scrubbing.
	 */
	for (i = 0; i < ARRAY_SIZE(scrubrates); i++) {
		/*
		 * skip scrub rates which aren't recommended
		 * (see F10 BKDG, F3x58)
		 */
		if (scrubrates[i].scrubval < min_rate)
			continue;

		if (scrubrates[i].bandwidth <= new_bw)
			break;

		/*
		 * if no suitable bandwidth found, turn off DRAM scrubbing
		 * entirely by falling back to the last element in the
		 * scrubrates array.
		 */
	}

	scrubval = scrubrates[i].scrubval;

	pci_write_bits32(ctl, SCRCTRL, scrubval, 0x001F);

	if (scrubval)
		return scrubrates[i].bandwidth;

	return 0;
}
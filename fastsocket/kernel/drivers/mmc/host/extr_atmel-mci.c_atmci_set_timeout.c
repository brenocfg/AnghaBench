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
struct mmc_data {unsigned int timeout_clks; int /*<<< orphan*/  timeout_ns; } ;
struct atmel_mci_slot {TYPE_1__* mmc; } ;
struct atmel_mci {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTOR ; 
 int MCI_DTOCYC (unsigned int) ; 
 int MCI_DTOMUL (unsigned int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  mci_writel (struct atmel_mci*,int /*<<< orphan*/ ,int) ; 
 unsigned int ns_to_clocks (struct atmel_mci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmci_set_timeout(struct atmel_mci *host,
		struct atmel_mci_slot *slot, struct mmc_data *data)
{
	static unsigned	dtomul_to_shift[] = {
		0, 4, 7, 8, 10, 12, 16, 20
	};
	unsigned	timeout;
	unsigned	dtocyc;
	unsigned	dtomul;

	timeout = ns_to_clocks(host, data->timeout_ns) + data->timeout_clks;

	for (dtomul = 0; dtomul < 8; dtomul++) {
		unsigned shift = dtomul_to_shift[dtomul];
		dtocyc = (timeout + (1 << shift) - 1) >> shift;
		if (dtocyc < 15)
			break;
	}

	if (dtomul >= 8) {
		dtomul = 7;
		dtocyc = 15;
	}

	dev_vdbg(&slot->mmc->class_dev, "setting timeout to %u cycles\n",
			dtocyc << dtomul_to_shift[dtomul]);
	mci_writel(host, DTOR, (MCI_DTOMUL(dtomul) | MCI_DTOCYC(dtocyc)));
}
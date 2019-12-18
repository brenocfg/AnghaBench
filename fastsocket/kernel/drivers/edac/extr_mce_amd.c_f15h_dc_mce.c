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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ BUS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static bool f15h_dc_mce(u16 ec, u8 xec)
{
	bool ret = true;

	if (MEM_ERROR(ec)) {

		switch (xec) {
		case 0x0:
			pr_cont("Data Array access error.\n");
			break;

		case 0x1:
			pr_cont("UC error during a linefill from L2/NB.\n");
			break;

		case 0x2:
		case 0x11:
			pr_cont("STQ access error.\n");
			break;

		case 0x3:
			pr_cont("SCB access error.\n");
			break;

		case 0x10:
			pr_cont("Tag error.\n");
			break;

		case 0x12:
			pr_cont("LDQ access error.\n");
			break;

		default:
			ret = false;
		}
	} else if (BUS_ERROR(ec)) {

		if (!xec)
			pr_cont("during system linefill.\n");
		else
			pr_cont(" Internal %s condition.\n",
				((xec == 1) ? "livelock" : "deadlock"));
	} else
		ret = false;

	return ret;
}
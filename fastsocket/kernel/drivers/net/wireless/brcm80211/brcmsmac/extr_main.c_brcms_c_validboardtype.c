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
struct brcms_hardware {int boardrev; int /*<<< orphan*/  sih; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_BROADCOM ; 
 scalar_t__ ai_get_boardvendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool brcms_c_validboardtype(struct brcms_hardware *wlc_hw)
{
	uint boardrev = wlc_hw->boardrev;

	/* 4 bits each for board type, major, minor, and tiny version */
	uint brt = (boardrev & 0xf000) >> 12;
	uint b0 = (boardrev & 0xf00) >> 8;
	uint b1 = (boardrev & 0xf0) >> 4;
	uint b2 = boardrev & 0xf;

	/* voards from other vendors are always considered valid */
	if (ai_get_boardvendor(wlc_hw->sih) != PCI_VENDOR_ID_BROADCOM)
		return true;

	/* do some boardrev sanity checks when boardvendor is Broadcom */
	if (boardrev == 0)
		return false;

	if (boardrev <= 0xff)
		return true;

	if ((brt > 2) || (brt == 0) || (b0 > 9) || (b0 == 0) || (b1 > 9)
		|| (b2 > 9))
		return false;

	return true;
}
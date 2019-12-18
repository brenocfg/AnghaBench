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
struct zd_ioreq16 {int member_1; int value; int /*<<< orphan*/  member_0; } ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16*) ; 
 int /*<<< orphan*/  ZD_CR128 ; 
 int /*<<< orphan*/  ZD_CR129 ; 
 int /*<<< orphan*/  ZD_CR130 ; 
 int /*<<< orphan*/  ZD_CR47 ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16*,int /*<<< orphan*/ ) ; 

int zd_chip_generic_patch_6m_band(struct zd_chip *chip, int channel)
{
	struct zd_ioreq16 ioreqs[] = {
		{ ZD_CR128, 0x14 }, { ZD_CR129, 0x12 }, { ZD_CR130, 0x10 },
		{ ZD_CR47,  0x1e },
	};

	/* FIXME: Channel 11 is not the edge for all regulatory domains. */
	if (channel == 1 || channel == 11)
		ioreqs[0].value = 0x12;

	dev_dbg_f(zd_chip_dev(chip), "patching for channel %d\n", channel);
	return zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
}
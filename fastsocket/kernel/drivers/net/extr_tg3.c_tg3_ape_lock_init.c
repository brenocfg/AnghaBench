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
struct tg3 {int pci_fn; } ;

/* Variables and functions */
 int APE_LOCK_GRANT_DRIVER ; 
 scalar_t__ ASIC_REV_5761 ; 
 int TG3_APE_LOCK_GPIO ; 
 int TG3_APE_LOCK_GRANT ; 
#define  TG3_APE_LOCK_PHY0 131 
#define  TG3_APE_LOCK_PHY1 130 
#define  TG3_APE_LOCK_PHY2 129 
#define  TG3_APE_LOCK_PHY3 128 
 int TG3_APE_PER_LOCK_GRANT ; 
 int /*<<< orphan*/  tg3_ape_write32 (struct tg3*,int,int) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 

__attribute__((used)) static void tg3_ape_lock_init(struct tg3 *tp)
{
	int i;
	u32 regbase, bit;

	if (tg3_asic_rev(tp) == ASIC_REV_5761)
		regbase = TG3_APE_LOCK_GRANT;
	else
		regbase = TG3_APE_PER_LOCK_GRANT;

	/* Make sure the driver hasn't any stale locks. */
	for (i = TG3_APE_LOCK_PHY0; i <= TG3_APE_LOCK_GPIO; i++) {
		switch (i) {
		case TG3_APE_LOCK_PHY0:
		case TG3_APE_LOCK_PHY1:
		case TG3_APE_LOCK_PHY2:
		case TG3_APE_LOCK_PHY3:
			bit = APE_LOCK_GRANT_DRIVER;
			break;
		default:
			if (!tp->pci_fn)
				bit = APE_LOCK_GRANT_DRIVER;
			else
				bit = 1 << tp->pci_fn;
		}
		tg3_ape_write32(tp, regbase + 4 * i, bit);
	}

}
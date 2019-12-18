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
typedef  int u16 ;
struct b43_phy {int rev; int radio_rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int** r2057_rev4_init ; 
 int** r2057_rev5_init ; 
 int** r2057_rev5a_init ; 
 int** r2057_rev7_init ; 
 int** r2057_rev8_init ; 

void r2057_upload_inittabs(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	u16 *table = NULL;
	u16 size, i;

	if (phy->rev == 7) {
		table = r2057_rev4_init[0];
		size = ARRAY_SIZE(r2057_rev4_init);
	} else if (phy->rev == 8 || phy->rev == 9) {
		if (phy->radio_rev == 5) {
			if (phy->radio_rev == 8) {
				table = r2057_rev5_init[0];
				size = ARRAY_SIZE(r2057_rev5_init);
			} else {
				table = r2057_rev5a_init[0];
				size = ARRAY_SIZE(r2057_rev5a_init);
			}
		} else if (phy->radio_rev == 7) {
			table = r2057_rev7_init[0];
			size = ARRAY_SIZE(r2057_rev7_init);
		} else if (phy->radio_rev == 9) {
			table = r2057_rev8_init[0];
			size = ARRAY_SIZE(r2057_rev8_init);
		}
	}

	if (table) {
		for (i = 0; i < 10; i++) {
			pr_info("radio_write 0x%X ", *table);
			table++;
			pr_info("0x%X\n", *table);
			table++;
		}
	}
}
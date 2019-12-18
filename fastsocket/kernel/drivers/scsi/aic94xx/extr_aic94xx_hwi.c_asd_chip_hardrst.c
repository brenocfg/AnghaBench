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
struct asd_ha_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIMINT ; 
 int /*<<< orphan*/  COMBIST ; 
 int ENODEV ; 
 int HARDRST ; 
 int HARDRSTDET ; 
 int PORRSTDET ; 
 int asd_read_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int asd_chip_hardrst(struct asd_ha_struct *asd_ha)
{
	int i;
	int count = 100;
	u32 reg;

	for (i = 0 ; i < 4 ; i++) {
		asd_write_reg_dword(asd_ha, COMBIST, HARDRST);
	}

	do {
		udelay(1);
		reg = asd_read_reg_dword(asd_ha, CHIMINT);
		if (reg & HARDRSTDET) {
			asd_write_reg_dword(asd_ha, CHIMINT,
					    HARDRSTDET|PORRSTDET);
			return 0;
		}
	} while (--count > 0);

	return -ENODEV;
}
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

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pm3386_get_mac (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm3386_reg_write (int,int,int) ; 
 int pm3386_secondary_present () ; 
 int /*<<< orphan*/  pm3386_set_carrier (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm3386_set_mac (int,int /*<<< orphan*/ *) ; 

void pm3386_reset(void)
{
	u8 mac[3][6];
	int secondary;

	secondary = pm3386_secondary_present();

	/* Save programmed MAC addresses.  */
	pm3386_get_mac(0, mac[0]);
	pm3386_get_mac(1, mac[1]);
	if (secondary)
		pm3386_get_mac(2, mac[2]);

	/* Assert analog and digital reset.  */
	pm3386_reg_write(0, 0x002, 0x0060);
	if (secondary)
		pm3386_reg_write(1, 0x002, 0x0060);
	mdelay(1);

	/* Deassert analog reset.  */
	pm3386_reg_write(0, 0x002, 0x0062);
	if (secondary)
		pm3386_reg_write(1, 0x002, 0x0062);
	mdelay(10);

	/* Deassert digital reset.  */
	pm3386_reg_write(0, 0x002, 0x0063);
	if (secondary)
		pm3386_reg_write(1, 0x002, 0x0063);
	mdelay(10);

	/* Restore programmed MAC addresses.  */
	pm3386_set_mac(0, mac[0]);
	pm3386_set_mac(1, mac[1]);
	if (secondary)
		pm3386_set_mac(2, mac[2]);

	/* Disable carrier on all ports.  */
	pm3386_set_carrier(0, 0);
	pm3386_set_carrier(1, 0);
	if (secondary)
		pm3386_set_carrier(2, 0);
}
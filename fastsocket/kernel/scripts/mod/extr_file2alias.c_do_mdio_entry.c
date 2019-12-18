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
struct mdio_device_id {int phy_id_mask; int phy_id; } ;

/* Variables and functions */
 char* MDIO_MODULE_PREFIX ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static int do_mdio_entry(const char *filename,
			 struct mdio_device_id *id, char *alias)
{
	int i;

	alias += sprintf(alias, MDIO_MODULE_PREFIX);

	for (i = 0; i < 32; i++) {
		if (!((id->phy_id_mask >> (31-i)) & 1))
			*(alias++) = '?';
		else if ((id->phy_id >> (31-i)) & 1)
			*(alias++) = '1';
		else
			*(alias++) = '0';
	}

	/* Terminate the string */
	*alias = 0;

	return 1;
}
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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  celleb_fake_config_readb (char*) ; 
 int /*<<< orphan*/  celleb_fake_config_readl (char*) ; 
 int /*<<< orphan*/  celleb_fake_config_readw (char*) ; 

__attribute__((used)) static void celleb_config_read_fake(unsigned char *config, int where,
				    int size, u32 *val)
{
	char *p = config + where;

	switch (size) {
	case 1:
		*val = celleb_fake_config_readb(p);
		break;
	case 2:
		*val = celleb_fake_config_readw(p);
		break;
	case 4:
		*val = celleb_fake_config_readl(p);
		break;
	}
}
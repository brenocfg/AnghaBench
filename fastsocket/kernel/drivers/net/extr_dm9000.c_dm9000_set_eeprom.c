#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {int offset; int len; scalar_t__ magic; } ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int DM9000_PLATF_NO_EEPROM ; 
 scalar_t__ DM_EEPROM_MAGIC ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  dm9000_write_eeprom (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_dm9000_board (struct net_device*) ; 

__attribute__((used)) static int dm9000_set_eeprom(struct net_device *dev,
			     struct ethtool_eeprom *ee, u8 *data)
{
	board_info_t *dm = to_dm9000_board(dev);
	int offset = ee->offset;
	int len = ee->len;
	int i;

	/* EEPROM access is aligned to two bytes */

	if ((len & 1) != 0 || (offset & 1) != 0)
		return -EINVAL;

	if (dm->flags & DM9000_PLATF_NO_EEPROM)
		return -ENOENT;

	if (ee->magic != DM_EEPROM_MAGIC)
		return -EINVAL;

	for (i = 0; i < len; i += 2)
		dm9000_write_eeprom(dm, (offset + i) / 2, data + i);

	return 0;
}
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
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** dm_shadow ; 
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int) ; 

void dm_shadow_init(struct net_device *dev)
{
	u8	page;
	u16	offset;

	for (page = 0; page < 5; page++)
		for (offset = 0; offset < 256; offset++)
		{
			dm_shadow[page][offset] = read_nic_byte(dev, offset+page*256);
			//DbgPrint("P-%d/O-%02x=%02x\r\n", page, offset, DM_Shadow[page][offset]);
		}

	for (page = 8; page < 11; page++)
		for (offset = 0; offset < 256; offset++)
			dm_shadow[page][offset] = read_nic_byte(dev, offset+page*256);

	for (page = 12; page < 15; page++)
		for (offset = 0; offset < 256; offset++)
			dm_shadow[page][offset] = read_nic_byte(dev, offset+page*256);

}
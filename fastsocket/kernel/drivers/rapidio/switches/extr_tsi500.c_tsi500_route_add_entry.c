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
typedef  int u32 ;
typedef  int u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rio_mport_read_config_32 (struct rio_mport*,int,int,int,int*) ; 
 int /*<<< orphan*/  rio_mport_write_config_32 (struct rio_mport*,int,int,int,int) ; 

__attribute__((used)) static int
tsi500_route_add_entry(struct rio_mport *mport, u16 destid, u8 hopcount, u16 table, u16 route_destid, u8 route_port)
{
	int i;
	u32 offset = 0x10000 + 0xa00 + ((route_destid / 2)&~0x3);
	u32 result;

	if (table == 0xff) {
		rio_mport_read_config_32(mport, destid, hopcount, offset, &result);
		result &= ~(0xf << (4*(route_destid & 0x7)));
		for (i=0;i<4;i++)
			rio_mport_write_config_32(mport, destid, hopcount, offset + (0x20000*i), result | (route_port << (4*(route_destid & 0x7))));
	}
	else {
		rio_mport_read_config_32(mport, destid, hopcount, offset + (0x20000*table), &result);
		result &= ~(0xf << (4*(route_destid & 0x7)));
		rio_mport_write_config_32(mport, destid, hopcount, offset + (0x20000*table), result | (route_port << (4*(route_destid & 0x7))));
	}

	return 0;
}
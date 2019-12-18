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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  efuse_PgPacketWrite (struct net_device*,int,int,int*) ; 
 int /*<<< orphan*/  efuse_PowerSwitch (struct net_device*,int /*<<< orphan*/ ) ; 

extern	void
EFUSE_ForceWriteVendorId( struct net_device* dev)
{
	u8 tmpdata[8] = {0xFF, 0xFF, 0xEC, 0x10, 0xFF, 0xFF, 0xFF, 0xFF};

	efuse_PowerSwitch(dev, TRUE);

	efuse_PgPacketWrite(dev, 1, 0xD, tmpdata);

	efuse_PowerSwitch(dev, FALSE);

}
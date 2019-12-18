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
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PhyAddr ; 
 int /*<<< orphan*/  PhyDataR ; 
 int /*<<< orphan*/  PlatformIORead1Byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlatformIOWrite4Byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

u8
ReadBBPortUchar(
	struct net_device *dev,
	u32		addr
	)
{
	//u8	TimeoutCounter;
	u8	RegisterContent;

	PlatformIOWrite4Byte(dev, PhyAddr, addr & 0xffffff7f);
	RegisterContent = PlatformIORead1Byte(dev, PhyDataR);

	return RegisterContent;
}
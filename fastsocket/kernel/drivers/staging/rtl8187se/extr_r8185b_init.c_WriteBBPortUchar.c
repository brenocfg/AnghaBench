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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PhyAddr ; 
 int /*<<< orphan*/  PhyDataR ; 
 scalar_t__ PlatformIORead1Byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlatformIOWrite4Byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void
WriteBBPortUchar(
	struct net_device *dev,
	u32		Data
	)
{
	//u8	TimeoutCounter;
	u8	RegisterContent;
	u8	UCharData;

	UCharData = (u8)((Data & 0x0000ff00) >> 8);
	PlatformIOWrite4Byte(dev, PhyAddr, Data);
	//for(TimeoutCounter = 10; TimeoutCounter > 0; TimeoutCounter--)
	{
		PlatformIOWrite4Byte(dev, PhyAddr, Data & 0xffffff7f);
		RegisterContent = PlatformIORead1Byte(dev, PhyDataR);
		//if(UCharData == RegisterContent)
		//	break;
	}
}
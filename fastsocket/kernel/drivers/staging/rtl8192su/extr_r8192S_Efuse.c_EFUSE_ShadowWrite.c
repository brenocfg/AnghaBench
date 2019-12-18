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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  efuse_ShadowWrite1Byte (struct net_device*,int,int) ; 
 int /*<<< orphan*/  efuse_ShadowWrite2Byte (struct net_device*,int,int) ; 
 int /*<<< orphan*/  efuse_ShadowWrite4Byte (struct net_device*,int,scalar_t__) ; 

extern	void
EFUSE_ShadowWrite(	struct net_device*	dev,	u8 Type, u16 Offset,u32	Value)
{
	//HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(pAdapter);

	if (Offset >= 0x18 && Offset <= 0x1F)
		return;

	if (Type == 1)
		efuse_ShadowWrite1Byte(dev, Offset, (u8)Value);
	else if (Type == 2)
		efuse_ShadowWrite2Byte(dev, Offset, (u16)Value);
	else if (Type == 4)
		efuse_ShadowWrite4Byte(dev, Offset, (u32)Value);

}
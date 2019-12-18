#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {size_t Value; int Driver_Write; } ;

/* Variables and functions */
 TYPE_1__** RF_Shadow ; 
 size_t bRFRegOffsetMask ; 

extern void PHY_RFShadowWrite(
	struct net_device		* dev,
	u32	eRFPath,
	u32					Offset,
	u32					Data)
{
	//RF_Shadow[eRFPath][Offset].Value = (Data & bMask20Bits);
	RF_Shadow[eRFPath][Offset].Value = (Data & bRFRegOffsetMask);
	RF_Shadow[eRFPath][Offset].Driver_Write = true;

}
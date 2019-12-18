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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  Recorver; } ;
typedef  size_t RF90_RADIO_PATH_E ;

/* Variables and functions */
 TYPE_1__** RF_Shadow ; 

extern void PHY_RFShadowRecorverFlagSet(
	struct net_device 		* dev,
	RF90_RADIO_PATH_E	eRFPath,
	u32					Offset,
	u8					Type)
{
	// Set True or False!!!
	RF_Shadow[eRFPath][Offset].Recorver= Type;

}
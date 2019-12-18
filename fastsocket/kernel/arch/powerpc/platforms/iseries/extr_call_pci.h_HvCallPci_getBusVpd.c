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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int HvCall4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvCallPciGetCardVpd ; 
 int /*<<< orphan*/  HvCallPci_BusVpd ; 

__attribute__((used)) static inline int HvCallPci_getBusVpd(u16 busNumParm, u64 destParm,
		u16 sizeParm)
{
	u64 xRc = HvCall4(HvCallPciGetCardVpd, busNumParm, destParm,
			sizeParm, HvCallPci_BusVpd);
	if (xRc == -1)
		return -1;
	else
		return xRc & 0xFFFF;
}
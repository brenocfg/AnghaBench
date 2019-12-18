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
typedef  int u32 ;
struct cmac {int /*<<< orphan*/  adapter; TYPE_1__* instance; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int /*<<< orphan*/  REG_HIGH_LOW_WM (int,int) ; 
 int /*<<< orphan*/  REG_MODE_CFG (int) ; 
 int WM_ENABLE ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mac_enable(struct cmac *mac, int which)
{
	u32 val;
	int port = mac->instance->index;

	/* Write the correct WM value when the port is enabled. */
	vsc_write(mac->adapter, REG_HIGH_LOW_WM(1,port), WM_ENABLE);

	vsc_read(mac->adapter, REG_MODE_CFG(port), &val);
	if (which & MAC_DIRECTION_RX)
		val |= 0x2;
	if (which & MAC_DIRECTION_TX)
		val |= 1;
	vsc_write(mac->adapter, REG_MODE_CFG(port), val);
	return 0;
}
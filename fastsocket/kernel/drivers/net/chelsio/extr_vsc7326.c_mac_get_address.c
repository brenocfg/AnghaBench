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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct cmac {int /*<<< orphan*/  adapter; TYPE_1__* instance; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MAC_HIGH_ADDR (int) ; 
 int /*<<< orphan*/  REG_MAC_LOW_ADDR (int) ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mac_get_address(struct cmac *mac, u8 addr[6])
{
	u32 addr_lo, addr_hi;
	int port = mac->instance->index;

	vsc_read(mac->adapter, REG_MAC_LOW_ADDR(port), &addr_lo);
	vsc_read(mac->adapter, REG_MAC_HIGH_ADDR(port), &addr_hi);

	addr[0] = (u8) (addr_hi >> 16);
	addr[1] = (u8) (addr_hi >> 8);
	addr[2] = (u8) addr_hi;
	addr[3] = (u8) (addr_lo >> 16);
	addr[4] = (u8) (addr_lo >> 8);
	addr[5] = (u8) addr_lo;
	return 0;
}
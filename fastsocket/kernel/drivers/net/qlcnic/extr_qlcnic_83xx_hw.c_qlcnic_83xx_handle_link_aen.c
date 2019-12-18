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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int has_link_events; int /*<<< orphan*/  link_duplex; void* module_type; void* link_autoneg; int /*<<< orphan*/  link_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int LSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LSW (int /*<<< orphan*/ ) ; 
 void* MSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_advert_link_change (struct qlcnic_adapter*,int) ; 

__attribute__((used)) static void qlcnic_83xx_handle_link_aen(struct qlcnic_adapter *adapter,
					u32 data[])
{
	u8 link_status, duplex;
	/* link speed */
	link_status = LSB(data[3]) & 1;
	adapter->ahw->link_speed = MSW(data[2]);
	adapter->ahw->link_autoneg = MSB(MSW(data[3]));
	adapter->ahw->module_type = MSB(LSW(data[3]));
	duplex = LSB(MSW(data[3]));
	if (duplex)
		adapter->ahw->link_duplex = DUPLEX_FULL;
	else
		adapter->ahw->link_duplex = DUPLEX_HALF;
	adapter->ahw->has_link_events = 1;
	qlcnic_advert_link_change(adapter, link_status);
}
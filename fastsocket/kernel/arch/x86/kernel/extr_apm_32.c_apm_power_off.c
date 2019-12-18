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
typedef  int /*<<< orphan*/  po_bios_call ;
struct TYPE_2__ {scalar_t__ realmode_power_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_STATE_OFF ; 
 TYPE_1__ apm_info ; 
 int /*<<< orphan*/  cpumask_of (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  machine_real_restart (unsigned char*,int) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_system_power_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apm_power_off(void)
{
	unsigned char po_bios_call[] = {
		0xb8, 0x00, 0x10,	/* movw  $0x1000,ax  */
		0x8e, 0xd0,		/* movw  ax,ss       */
		0xbc, 0x00, 0xf0,	/* movw  $0xf000,sp  */
		0xb8, 0x07, 0x53,	/* movw  $0x5307,ax  */
		0xbb, 0x01, 0x00,	/* movw  $0x0001,bx  */
		0xb9, 0x03, 0x00,	/* movw  $0x0003,cx  */
		0xcd, 0x15		/* int   $0x15       */
	};

	/* Some bioses don't like being called from CPU != 0 */
	if (apm_info.realmode_power_off) {
		set_cpus_allowed_ptr(current, cpumask_of(0));
		machine_real_restart(po_bios_call, sizeof(po_bios_call));
	} else {
		(void)set_system_power_state(APM_STATE_OFF);
	}
}
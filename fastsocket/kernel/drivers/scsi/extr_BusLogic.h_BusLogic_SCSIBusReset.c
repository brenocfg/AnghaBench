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
struct TYPE_2__ {int SCSIBusReset; } ;
union BusLogic_ControlRegister {scalar_t__ All; TYPE_1__ cr; } ;
struct BusLogic_HostAdapter {scalar_t__ IO_Address; } ;

/* Variables and functions */
 scalar_t__ BusLogic_ControlRegisterOffset ; 
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void BusLogic_SCSIBusReset(struct BusLogic_HostAdapter *HostAdapter)
{
	union BusLogic_ControlRegister ControlRegister;
	ControlRegister.All = 0;
	ControlRegister.cr.SCSIBusReset = true;
	outb(ControlRegister.All, HostAdapter->IO_Address + BusLogic_ControlRegisterOffset);
}
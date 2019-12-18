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
typedef  int u32 ;
struct fw_ohci {int /*<<< orphan*/  bus_seconds; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_IsochronousCycleTimer ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct fw_ohci* fw_ohci (struct fw_card*) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ohci_get_bus_time(struct fw_card *card)
{
	struct fw_ohci *ohci = fw_ohci(card);
	u32 cycle_time;
	u64 bus_time;

	cycle_time = reg_read(ohci, OHCI1394_IsochronousCycleTimer);
	bus_time = ((u64)atomic_read(&ohci->bus_seconds) << 32) | cycle_time;

	return bus_time;
}
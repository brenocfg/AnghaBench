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
struct Scsi_Host {scalar_t__ hostdata; } ;
struct BusLogic_HostAdapter {char const* FullModelName; } ;

/* Variables and functions */

__attribute__((used)) static const char *BusLogic_DriverInfo(struct Scsi_Host *Host)
{
	struct BusLogic_HostAdapter *HostAdapter = (struct BusLogic_HostAdapter *) Host->hostdata;
	return HostAdapter->FullModelName;
}
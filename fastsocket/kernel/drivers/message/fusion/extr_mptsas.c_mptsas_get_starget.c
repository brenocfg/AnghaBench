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
struct scsi_target {int dummy; } ;
struct mptsas_phyinfo {TYPE_1__* port_details; } ;
struct TYPE_2__ {struct scsi_target* starget; } ;

/* Variables and functions */

__attribute__((used)) static inline struct scsi_target *
mptsas_get_starget(struct mptsas_phyinfo *phy_info)
{
	if (phy_info->port_details)
		return phy_info->port_details->starget;
	else
		return NULL;
}
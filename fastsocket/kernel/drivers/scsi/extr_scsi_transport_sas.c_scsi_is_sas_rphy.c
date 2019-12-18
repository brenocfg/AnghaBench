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
struct device {scalar_t__ release; } ;

/* Variables and functions */
 scalar_t__ sas_end_device_release ; 
 scalar_t__ sas_expander_release ; 

int scsi_is_sas_rphy(const struct device *dev)
{
	return dev->release == sas_end_device_release ||
		dev->release == sas_expander_release;
}
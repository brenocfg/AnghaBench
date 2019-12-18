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
struct scsi_host_template {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 scalar_t__ ips ; 
 int /*<<< orphan*/  ips_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ips_ha ; 
 int ips_hotplug ; 
 int ips_num_controllers ; 
 scalar_t__ ips_register_scsi (int) ; 
 int /*<<< orphan*/  ips_released_controllers ; 
 int /*<<< orphan*/  ips_setup (scalar_t__) ; 

__attribute__((used)) static int
ips_detect(struct scsi_host_template * SHT)
{
	int i;

	METHOD_TRACE("ips_detect", 1);

#ifdef MODULE
	if (ips)
		ips_setup(ips);
#endif

	for (i = 0; i < ips_num_controllers; i++) {
		if (ips_register_scsi(i))
			ips_free(ips_ha[i]);
		ips_released_controllers++;
	}
	ips_hotplug = 1;
	return (ips_num_controllers);
}
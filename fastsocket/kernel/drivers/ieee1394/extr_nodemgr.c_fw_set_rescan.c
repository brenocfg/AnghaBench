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
struct bus_type {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int bus_rescan_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee1394_bus_type ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t fw_set_rescan(struct bus_type *bus, const char *buf,
			     size_t count)
{
	int error = 0;

	if (simple_strtoul(buf, NULL, 10) == 1)
		error = bus_rescan_devices(&ieee1394_bus_type);
	return error ? error : count;
}
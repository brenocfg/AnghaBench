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
typedef  size_t ssize_t ;

/* Variables and functions */
 int ignore_drivers ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t fw_set_ignore_drivers(struct bus_type *bus, const char *buf, size_t count)
{
	int state = simple_strtoul(buf, NULL, 10);

	if (state == 1)
		ignore_drivers = 1;
	else if (state == 0)
		ignore_drivers = 0;

	return count;
}
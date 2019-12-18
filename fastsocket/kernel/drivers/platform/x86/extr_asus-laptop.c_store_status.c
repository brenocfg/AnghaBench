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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int parse_arg (char const*,size_t,int*) ; 
 int /*<<< orphan*/  write_status (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static ssize_t store_status(const char *buf, size_t count,
			    acpi_handle handle, int mask)
{
	int rv, value;
	int out = 0;

	rv = parse_arg(buf, count, &value);
	if (rv > 0)
		out = value ? 1 : 0;

	write_status(handle, out, mask);

	return rv;
}
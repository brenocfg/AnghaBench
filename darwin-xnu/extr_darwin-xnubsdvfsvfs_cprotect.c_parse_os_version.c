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
typedef  int cp_key_os_version_t ;

/* Variables and functions */

__attribute__((used)) static cp_key_os_version_t
parse_os_version(const char *vers)
{
	const char *p = vers;

	int a = 0;
	while (*p >= '0' && *p <= '9') {
		a = a * 10 + *p - '0';
		++p;
	}

	if (!a)
		return 0;

	int b = *p++;
	if (!b)
		return 0;

	int c = 0;
	while (*p >= '0' && *p <= '9') {
		c = c * 10 + *p - '0';
		++p;
	}

	if (!c)
		return 0;

	return (a & 0xff) << 24 | b << 16 | (c & 0xffff);
}
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
struct ifaddrs {int /*<<< orphan*/  ifa_name; struct ifaddrs* ifa_next; } ;

/* Variables and functions */
 struct ifaddrs* ifas ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
conf_is_interface(const char *name)
{
	const struct ifaddrs *ifa;

	for (ifa = ifas; ifa; ifa = ifa->ifa_next)
		if (strcmp(ifa->ifa_name, name) == 0)
			return 1;
	return 0;
}
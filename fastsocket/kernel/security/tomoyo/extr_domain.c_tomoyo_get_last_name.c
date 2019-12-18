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
struct tomoyo_domain_info {TYPE_1__* domainname; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 char* strrchr (char const*,char) ; 

const char *tomoyo_get_last_name(const struct tomoyo_domain_info *domain)
{
	const char *cp0 = domain->domainname->name;
	const char *cp1 = strrchr(cp0, ' ');

	if (cp1)
		return cp1 + 1;
	return cp0;
}
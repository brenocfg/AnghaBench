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

/* Variables and functions */
 char* strstr (char*,char*) ; 
 int tomoyo_update_domain_keeper_entry (char*,char*,int const,int const) ; 

int tomoyo_write_domain_keeper_policy(char *data, const bool is_not,
				      const bool is_delete)
{
	char *cp = strstr(data, " from ");

	if (cp) {
		*cp = '\0';
		return tomoyo_update_domain_keeper_entry(cp + 6, data, is_not,
							 is_delete);
	}
	return tomoyo_update_domain_keeper_entry(data, NULL, is_not, is_delete);
}
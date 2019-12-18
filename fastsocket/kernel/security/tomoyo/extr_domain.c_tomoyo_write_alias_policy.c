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
 int EINVAL ; 
 char* strchr (char*,char) ; 
 int tomoyo_update_alias_entry (char*,char*,int const) ; 

int tomoyo_write_alias_policy(char *data, const bool is_delete)
{
	char *cp = strchr(data, ' ');

	if (!cp)
		return -EINVAL;
	*cp++ = '\0';
	return tomoyo_update_alias_entry(data, cp, is_delete);
}
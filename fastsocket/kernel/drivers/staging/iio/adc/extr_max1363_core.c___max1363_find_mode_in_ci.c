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
struct max1363_mode {int /*<<< orphan*/  name; } ;
struct max1363_chip_info {int num_modes; size_t* mode_list; } ;

/* Variables and functions */
 struct max1363_mode const* max1363_mode_table ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct max1363_mode
*__max1363_find_mode_in_ci(const struct max1363_chip_info *info,
				  const char *buf)
{
	int i;
	for (i = 0; i <  info->num_modes; i++)
		if (strcmp(max1363_mode_table[info->mode_list[i]].name, buf)
		    == 0)
			return &max1363_mode_table[info->mode_list[i]];
	return NULL;
}
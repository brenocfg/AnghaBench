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
 int tomoyo_update_file_pattern_entry (char*,int const) ; 

int tomoyo_write_pattern_policy(char *data, const bool is_delete)
{
	return tomoyo_update_file_pattern_entry(data, is_delete);
}
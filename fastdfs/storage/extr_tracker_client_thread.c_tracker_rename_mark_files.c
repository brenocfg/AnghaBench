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
 int storage_rename_mark_file (char const*,int const,char const*,int const) ; 
 scalar_t__ trunk_rename_mark_file (char const*,int const,char const*,int const) ; 

__attribute__((used)) static int tracker_rename_mark_files(const char *old_ip_addr, \
	const int old_port, const char *new_ip_addr, const int new_port)
{
	int result;

	result = storage_rename_mark_file(old_ip_addr, old_port, \
				new_ip_addr, new_port);
	result += trunk_rename_mark_file(old_ip_addr, old_port, \
					new_ip_addr, new_port);
	return result;
}
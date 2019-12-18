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
 int /*<<< orphan*/  g_server_port ; 
 char* get_mark_filename_by_id_and_port (char const*,int /*<<< orphan*/ ,char*,int const) ; 

__attribute__((used)) static char *get_mark_filename_by_id(const char *storage_id, \
		char *full_filename, const int filename_size)
{
	return get_mark_filename_by_id_and_port(storage_id, g_server_port, \
				full_filename, filename_size);
}
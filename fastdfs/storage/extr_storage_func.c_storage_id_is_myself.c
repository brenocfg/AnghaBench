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
 int /*<<< orphan*/  g_my_server_id_str ; 
 scalar_t__ g_use_storage_id ; 
 int is_local_host_ip (char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

bool storage_id_is_myself(const char *storage_id)
{
	if (g_use_storage_id)
	{
		return strcmp(storage_id, g_my_server_id_str) == 0;
	}
	else
	{
		return is_local_host_ip(storage_id);
	}
}
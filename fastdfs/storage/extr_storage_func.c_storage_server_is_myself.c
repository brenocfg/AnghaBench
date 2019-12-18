#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ip_addr; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ FDFSStorageBrief ;

/* Variables and functions */
 int /*<<< orphan*/  g_my_server_id_str ; 
 scalar_t__ g_use_storage_id ; 
 int is_local_host_ip (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool storage_server_is_myself(const FDFSStorageBrief *pStorageBrief)
{
	if (g_use_storage_id)
	{
		return strcmp(pStorageBrief->id, g_my_server_id_str) == 0;
	}
	else
	{
		return is_local_host_ip(pStorageBrief->ip_addr);
	}
}
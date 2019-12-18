#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int count; int alloc_size; int store_lookup; int store_server; int download_server; int store_path; char* store_group; int current_write_group; TYPE_1__* pStoreGroup; } ;
struct TYPE_3__ {char* group_name; } ;

/* Variables and functions */
 TYPE_2__ g_groups ; 
 int snprintf (char*,int const,char*,int,int,int,int,int,int,char*,char*,int) ; 

__attribute__((used)) static int fdfs_dump_groups_info(char *buff, const int buffSize)
{
	int total_len;

	total_len = snprintf(buff, buffSize, 
		"group count=%d\n"
		"group alloc_size=%d\n"
		"store_lookup=%d\n"
		"store_server=%d\n"
		"download_server=%d\n"
		"store_path=%d\n"
		"store_group=%s\n"
		"pStoreGroup=%s\n"
		"current_write_group=%d\n",
		g_groups.count, 
		g_groups.alloc_size, 
		g_groups.store_lookup, 
		g_groups.store_server, 
		g_groups.download_server, 
		g_groups.store_path, 
		g_groups.store_group, 
		g_groups.pStoreGroup != NULL ? 
			g_groups.pStoreGroup->group_name : "",
		g_groups.current_write_group
	);

	return total_len;
}
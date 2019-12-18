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
 scalar_t__ binlog_write_cache_len ; 
 int storage_binlog_fsync (int) ; 

int fdfs_binlog_sync_func(void *args)
{
	if (binlog_write_cache_len > 0)
	{
		return storage_binlog_fsync(true);
	}
	else
	{
		return 0;
	}
}
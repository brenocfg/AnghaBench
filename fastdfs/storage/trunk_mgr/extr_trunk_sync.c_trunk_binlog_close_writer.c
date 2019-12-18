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
 int /*<<< orphan*/  close (int) ; 
 int trunk_binlog_fd ; 
 int trunk_binlog_fsync (int const) ; 
 scalar_t__ trunk_binlog_write_cache_len ; 

__attribute__((used)) static int trunk_binlog_close_writer(const bool needLock)
{
	int result;
	if (trunk_binlog_write_cache_len > 0)
	{
		if ((result=trunk_binlog_fsync(needLock)) != 0)
		{
			return result;
		}
	}
	close(trunk_binlog_fd);
	trunk_binlog_fd = -1;
	return 0;
}
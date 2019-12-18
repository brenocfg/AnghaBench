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
 scalar_t__ g_current_time ; 
 scalar_t__ g_trunk_compress_binlog_min_interval ; 
 scalar_t__ g_trunk_last_compress_time ; 
 int /*<<< orphan*/  logInfo (char*) ; 
 int storage_trunk_do_save () ; 
 int /*<<< orphan*/  storage_write_to_sync_ini_file () ; 
 int trunk_binlog_compress_apply () ; 
 int trunk_binlog_compress_commit () ; 
 int /*<<< orphan*/  trunk_binlog_compress_rollback () ; 
 int trunk_unlink_all_mark_files () ; 

__attribute__((used)) static int storage_trunk_save()
{
	int result;

	if (!(g_trunk_compress_binlog_min_interval > 0 && \
		g_current_time - g_trunk_last_compress_time >
		g_trunk_compress_binlog_min_interval))
	{
		return storage_trunk_do_save();
	}

	logInfo("start compress trunk binlog ...");
	if ((result=trunk_binlog_compress_apply()) != 0)
	{
		return result;
	}

	if ((result=storage_trunk_do_save()) != 0)
	{
		trunk_binlog_compress_rollback();
		return result;
	}

	if ((result=trunk_binlog_compress_commit()) != 0)
	{
		trunk_binlog_compress_rollback();
		return result;
	}

	g_trunk_last_compress_time = g_current_time;
	storage_write_to_sync_ini_file();

	logInfo("compress trunk binlog done.");
	return trunk_unlink_all_mark_files();  //because the binlog file be compressed
}
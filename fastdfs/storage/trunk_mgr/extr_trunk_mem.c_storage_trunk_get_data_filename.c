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
 int /*<<< orphan*/  MAX_PATH_SIZE ; 
 char* STORAGE_TRUNK_DATA_FILENAME ; 
 char* g_fdfs_base_path ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 

char *storage_trunk_get_data_filename(char *full_filename)
{
	snprintf(full_filename, MAX_PATH_SIZE, "%s/data/%s", \
		g_fdfs_base_path, STORAGE_TRUNK_DATA_FILENAME);
	return full_filename;
}
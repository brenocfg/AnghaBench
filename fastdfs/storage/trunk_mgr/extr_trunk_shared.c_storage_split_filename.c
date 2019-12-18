#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char** paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPLIT_FILENAME_BODY (char const*,int*,char*,int,int) ; 
 TYPE_1__ g_fdfs_store_paths ; 

int storage_split_filename(const char *logic_filename, \
		int *filename_len, char *true_filename, char **ppStorePath)
{
	int store_path_index;

	SPLIT_FILENAME_BODY(logic_filename, filename_len, true_filename, \
		store_path_index, true);

	*ppStorePath = g_fdfs_store_paths.paths[store_path_index];

	return 0;
}
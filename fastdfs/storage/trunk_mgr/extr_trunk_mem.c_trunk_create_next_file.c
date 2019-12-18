#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  full_filename ;
struct TYPE_7__ {int sub_path_high; int sub_path_low; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_8__ {TYPE_2__ path; TYPE_1__ file; } ;
typedef  TYPE_3__ FDFSTrunkFullInfo ;

/* Variables and functions */
 int MAX_PATH_SIZE ; 
 int /*<<< orphan*/  base64_encode_ex (int /*<<< orphan*/ *,char*,int,char*,int*,int) ; 
 int /*<<< orphan*/  fileExists (char*) ; 
 scalar_t__ g_current_trunk_file_id ; 
 int /*<<< orphan*/  g_fdfs_base64_context ; 
 int /*<<< orphan*/  int2buff (scalar_t__,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  storage_get_store_path (char*,int,int*,int*) ; 
 int storage_write_to_sync_ini_file () ; 
 int /*<<< orphan*/  trunk_file_lock ; 
 int /*<<< orphan*/  trunk_get_full_filename (TYPE_3__*,char*,int) ; 
 int trunk_init_file (char*) ; 

__attribute__((used)) static int trunk_create_next_file(FDFSTrunkFullInfo *pTrunkInfo)
{
	char buff[32];
	int result;
	int filename_len;
	char short_filename[64];
	char full_filename[MAX_PATH_SIZE];
	int sub_path_high;
	int sub_path_low;

	while (1)
	{
		pthread_mutex_lock(&trunk_file_lock);
		pTrunkInfo->file.id = ++g_current_trunk_file_id;
		result = storage_write_to_sync_ini_file();
		pthread_mutex_unlock(&trunk_file_lock);
		if (result != 0)
		{
			return result;
		}

		int2buff(pTrunkInfo->file.id, buff);
		base64_encode_ex(&g_fdfs_base64_context, buff, sizeof(int), \
				short_filename, &filename_len, false);

		storage_get_store_path(short_filename, filename_len, \
					&sub_path_high, &sub_path_low);

		pTrunkInfo->path.sub_path_high = sub_path_high;
		pTrunkInfo->path.sub_path_low = sub_path_low;

		trunk_get_full_filename(pTrunkInfo, full_filename, \
			sizeof(full_filename));
		if (!fileExists(full_filename))
		{
			break;
		}
	}

	if ((result=trunk_init_file(full_filename)) != 0)
	{
		return result;
	}

	return 0;
}
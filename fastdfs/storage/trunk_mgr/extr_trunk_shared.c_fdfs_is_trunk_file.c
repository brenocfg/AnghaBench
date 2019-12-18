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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  FDFS_FILENAME_BASE64_LENGTH ; 
 int FDFS_LOGIC_FILE_PATH_LEN ; 
 int const FDFS_TRUNK_LOGIC_FILENAME_LENGTH ; 
 int IS_TRUNK_FILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base64_decode_auto (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  buff2long (char*) ; 
 int /*<<< orphan*/  g_fdfs_base64_context ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

bool fdfs_is_trunk_file(const char *remote_filename, const int filename_len)
{
	int buff_len;
	char buff[64];
	int64_t file_size;

	if (filename_len != FDFS_TRUNK_LOGIC_FILENAME_LENGTH) //not trunk file
	{
		return false;
	}

	memset(buff, 0, sizeof(buff));
	base64_decode_auto(&g_fdfs_base64_context, (char *)remote_filename + \
		FDFS_LOGIC_FILE_PATH_LEN, FDFS_FILENAME_BASE64_LENGTH, \
		buff, &buff_len);

	file_size = buff2long(buff + sizeof(int) * 2);
	return IS_TRUNK_FILE(file_size);
}
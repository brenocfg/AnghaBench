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
 int FDFS_FILE_EXT_NAME_MAX_LEN ; 

const char *fdfs_http_get_file_extension(const char *filename, \
		const int filename_len, int *ext_len)
{
	const char *pEnd;
	const char *pExtName;
	int i;

	pEnd = filename + filename_len;
	pExtName = pEnd - 1;
	for (i=0; i<FDFS_FILE_EXT_NAME_MAX_LEN && pExtName >= filename; \
		i++, pExtName--)
	{
		if (*pExtName == '.')
		{
			break;
		}
	}

	if (i < FDFS_FILE_EXT_NAME_MAX_LEN) //found
	{
		pExtName++;  //skip .
		*ext_len = pEnd - pExtName;
		return pExtName;
	}
	else
	{
		*ext_len = 0;
		return NULL;
	}
}
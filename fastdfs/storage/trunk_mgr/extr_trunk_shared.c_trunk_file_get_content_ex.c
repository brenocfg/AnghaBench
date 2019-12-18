#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  full_filename ;
struct TYPE_5__ {scalar_t__ offset; } ;
struct TYPE_6__ {TYPE_1__ file; } ;
typedef  TYPE_2__ FDFSTrunkFullInfo ;
typedef  int /*<<< orphan*/  FDFSStorePaths ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOSPC ; 
 scalar_t__ FDFS_TRUNK_FILE_HEADER_SIZE ; 
 int MAX_PATH_SIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fc_safe_read (int,char*,int const) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunk_get_full_filename_ex (int /*<<< orphan*/  const*,TYPE_2__ const*,char*,int) ; 

int trunk_file_get_content_ex(const FDFSStorePaths *pStorePaths, \
		const FDFSTrunkFullInfo *pTrunkInfo, const int file_size, \
		int *pfd, char *buff, const int buff_size)
{
	char full_filename[MAX_PATH_SIZE];
	int fd;
	int result;
	int read_bytes;

	if (file_size > buff_size)
	{
		return ENOSPC;
	}

	if (pfd != NULL)
	{
		fd = *pfd;
	}
	else
	{
		trunk_get_full_filename_ex(pStorePaths, pTrunkInfo, \
			full_filename, sizeof(full_filename));
		fd = open(full_filename, O_RDONLY);
		if (fd < 0)
		{
			return errno != 0 ? errno : EIO;
		}

		if (lseek(fd, pTrunkInfo->file.offset + \
			FDFS_TRUNK_FILE_HEADER_SIZE, SEEK_SET) < 0)
		{
			result = errno != 0 ? errno : EIO;
			close(fd);
			return result;
		}
	}

	read_bytes = fc_safe_read(fd, buff, file_size);
	if (read_bytes == file_size)
	{
		result = 0;
	}
	else
	{
		result = errno != 0 ? errno : EINVAL;
	}

	if (pfd == NULL)
	{
		close(fd);
	}

	return result;
}
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
struct TYPE_2__ {int /*<<< orphan*/  error; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ mz_stream_posix ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_OK ; 
 int MZ_OPEN_ERROR ; 
 int MZ_OPEN_MODE_APPEND ; 
 int MZ_OPEN_MODE_CREATE ; 
 int MZ_OPEN_MODE_READ ; 
 int MZ_OPEN_MODE_READWRITE ; 
 int MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  MZ_SEEK_END ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen64 (char const*,char const*) ; 
 int mz_stream_os_seek (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t mz_stream_os_open(void *stream, const char *path, int32_t mode)
{
    mz_stream_posix *posix = (mz_stream_posix *)stream;
    const char *mode_fopen = NULL;

    if (path == NULL)
        return MZ_PARAM_ERROR;

    if ((mode & MZ_OPEN_MODE_READWRITE) == MZ_OPEN_MODE_READ)
        mode_fopen = "rb";
    else if (mode & MZ_OPEN_MODE_APPEND)
        mode_fopen = "r+b";
    else if (mode & MZ_OPEN_MODE_CREATE)
        mode_fopen = "wb";
    else
        return MZ_OPEN_ERROR;

    posix->handle = fopen64(path, mode_fopen);
    if (posix->handle == NULL)
    {
        posix->error = errno;
        return MZ_OPEN_ERROR;
    }

    if (mode & MZ_OPEN_MODE_APPEND)
        return mz_stream_os_seek(stream, 0, MZ_SEEK_END);

    return MZ_OK;
}
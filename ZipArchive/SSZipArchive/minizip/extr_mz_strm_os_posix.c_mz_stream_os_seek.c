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
struct TYPE_2__ {int /*<<< orphan*/  error; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ mz_stream_posix ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_OK ; 
#define  MZ_SEEK_CUR 130 
#define  MZ_SEEK_END 129 
 int MZ_SEEK_ERROR ; 
#define  MZ_SEEK_SET 128 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fseeko64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int32_t mz_stream_os_seek(void *stream, int64_t offset, int32_t origin)
{
    mz_stream_posix *posix = (mz_stream_posix*)stream;
    int32_t fseek_origin = 0;

    switch (origin)
    {
        case MZ_SEEK_CUR:
            fseek_origin = SEEK_CUR;
            break;
        case MZ_SEEK_END:
            fseek_origin = SEEK_END;
            break;
        case MZ_SEEK_SET:
            fseek_origin = SEEK_SET;
            break;
        default:
            return MZ_SEEK_ERROR;
    }

    if (fseeko64(posix->handle, offset, fseek_origin) != 0)
    {
        posix->error = errno;
        return MZ_SEEK_ERROR;
    }

    return MZ_OK;
}
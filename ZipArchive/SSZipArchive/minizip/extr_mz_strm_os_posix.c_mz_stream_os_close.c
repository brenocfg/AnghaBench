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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_CLOSE_ERROR ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 

int32_t mz_stream_os_close(void *stream)
{
    mz_stream_posix *posix = (mz_stream_posix*)stream;
    int32_t closed = 0;
    if (posix->handle != NULL)
    {
        closed = fclose(posix->handle);
        posix->handle = NULL;
    }
    if (closed != 0)
    {
        posix->error = errno;
        return MZ_CLOSE_ERROR;
    }
    return MZ_OK;
}
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
typedef  int int64_t ;

/* Variables and functions */
 int MZ_TELL_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int ftello64 (int /*<<< orphan*/ ) ; 

int64_t mz_stream_os_tell(void *stream)
{
    mz_stream_posix *posix = (mz_stream_posix*)stream;
    int64_t position = ftello64(posix->handle);
    if (position == -1)
    {
        posix->error = errno;
        return MZ_TELL_ERROR;
    }
    return position;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {scalar_t__ disk_size; int mode; scalar_t__ current_disk; scalar_t__ number_disk; TYPE_1__ stream; } ;
typedef  TYPE_2__ mz_stream_split ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int MZ_OPEN_MODE_WRITE ; 
 scalar_t__ mz_stream_is_open (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_stream_split_close_disk (void*) ; 
 scalar_t__ mz_stream_split_open_disk (void*,scalar_t__) ; 

__attribute__((used)) static int32_t mz_stream_split_goto_disk(void *stream, int32_t number_disk)
{
    mz_stream_split *split = (mz_stream_split *)stream;
    int32_t err = MZ_OK;
    int32_t err_is_open = MZ_OK;

    err_is_open = mz_stream_is_open(split->stream.base);

    if ((split->disk_size == 0) && (split->mode & MZ_OPEN_MODE_WRITE))
    {
        if (err_is_open != MZ_OK)
            err = mz_stream_split_open_disk(stream, number_disk);
    }
    else if ((number_disk != split->current_disk) || (err_is_open != MZ_OK))
    {
        err = mz_stream_split_close_disk(stream);
        if (err == MZ_OK)
        {
            err = mz_stream_split_open_disk(stream, number_disk);
            if (err == MZ_OK)
                split->number_disk = number_disk;
        }
    }

    return err;
}
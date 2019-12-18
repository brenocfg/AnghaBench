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
struct TYPE_2__ {scalar_t__ position; scalar_t__ limit; scalar_t__ size; int mode; } ;
typedef  TYPE_1__ mz_stream_mem ;
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_OK ; 
 int MZ_OPEN_MODE_CREATE ; 
#define  MZ_SEEK_CUR 130 
#define  MZ_SEEK_END 129 
 int MZ_SEEK_ERROR ; 
#define  MZ_SEEK_SET 128 
 int mz_stream_mem_set_size (void*,int) ; 

int32_t mz_stream_mem_seek(void *stream, int64_t offset, int32_t origin)
{
    mz_stream_mem *mem = (mz_stream_mem *)stream;
    int64_t new_pos = 0;
    int32_t err = MZ_OK;

    switch (origin)
    {
        case MZ_SEEK_CUR:
            new_pos = mem->position + offset;
            break;
        case MZ_SEEK_END:
            new_pos = mem->limit + offset;
            break;
        case MZ_SEEK_SET:
            new_pos = offset;
            break;
        default:
            return MZ_SEEK_ERROR;
    }

    if (new_pos > mem->size)
    {
        if ((mem->mode & MZ_OPEN_MODE_CREATE) == 0)
            return MZ_SEEK_ERROR;

        err = mz_stream_mem_set_size(stream, (int32_t)new_pos);
        if (err != MZ_OK)
            return err;
    }
    else if (new_pos < 0)
    {
        return MZ_SEEK_ERROR;
    }

    mem->position = (int32_t)new_pos;
    return MZ_OK;
}
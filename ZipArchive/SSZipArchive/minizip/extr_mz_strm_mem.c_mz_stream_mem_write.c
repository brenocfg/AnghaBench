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
struct TYPE_2__ {scalar_t__ size; scalar_t__ position; int mode; scalar_t__ grow_size; scalar_t__ buffer; scalar_t__ limit; } ;
typedef  TYPE_1__ mz_stream_mem ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int MZ_OPEN_MODE_CREATE ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,scalar_t__) ; 
 scalar_t__ mz_stream_mem_set_size (void*,scalar_t__) ; 

int32_t mz_stream_mem_write(void *stream, const void *buf, int32_t size)
{
    mz_stream_mem *mem = (mz_stream_mem *)stream;
    int32_t new_size = 0;
    int32_t err = MZ_OK;

    if (size == 0)
        return size;

    if (size > mem->size - mem->position)
    {
        if (mem->mode & MZ_OPEN_MODE_CREATE)
        {
            new_size = mem->size;
            if (size < mem->grow_size)
                new_size += mem->grow_size;
            else
                new_size += size;

            err = mz_stream_mem_set_size(stream, new_size);
            if (err != MZ_OK)
                return err;
        }
        else
        {
            size = mem->size - mem->position;
        }
    }

    memcpy(mem->buffer + mem->position, buf, size);

    mem->position += size;
    if (mem->position > mem->limit)
        mem->limit = mem->position;

    return size;
}
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
struct TYPE_2__ {int mode; scalar_t__ size; scalar_t__ limit; int /*<<< orphan*/  grow_size; scalar_t__ position; } ;
typedef  TYPE_1__ mz_stream_mem ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_OK ; 
 int MZ_OPEN_MODE_CREATE ; 
 int /*<<< orphan*/  MZ_UNUSED (char const*) ; 
 int mz_stream_mem_set_size (void*,int /*<<< orphan*/ ) ; 

int32_t mz_stream_mem_open(void *stream, const char *path, int32_t mode)
{
    mz_stream_mem *mem = (mz_stream_mem *)stream;
    int32_t err = MZ_OK;

    MZ_UNUSED(path);

    mem->mode = mode;
    mem->limit = 0;
    mem->position = 0;

    if (mem->mode & MZ_OPEN_MODE_CREATE)
        err = mz_stream_mem_set_size(stream, mem->grow_size);
    else
        mem->limit = mem->size;

    return err;
}
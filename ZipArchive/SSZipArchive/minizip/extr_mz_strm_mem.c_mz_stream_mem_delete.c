#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; struct TYPE_3__* buffer; } ;
typedef  TYPE_1__ mz_stream_mem ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FREE (TYPE_1__*) ; 
 int MZ_OPEN_MODE_CREATE ; 

void mz_stream_mem_delete(void **stream)
{
    mz_stream_mem *mem = NULL;
    if (stream == NULL)
        return;
    mem = (mz_stream_mem *)*stream;
    if (mem != NULL)
    {
        if ((mem->mode & MZ_OPEN_MODE_CREATE) && (mem->buffer != NULL))
            MZ_FREE(mem->buffer);
        MZ_FREE(mem);
    }
    *stream = NULL;
}
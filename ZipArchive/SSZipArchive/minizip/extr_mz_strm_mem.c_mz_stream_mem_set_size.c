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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ mz_stream_mem ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_ALLOC (int /*<<< orphan*/ ) ; 
 scalar_t__ MZ_BUF_ERROR ; 
 int /*<<< orphan*/  MZ_FREE (int /*<<< orphan*/ *) ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int32_t mz_stream_mem_set_size(void *stream, int32_t size)
{
    mz_stream_mem *mem = (mz_stream_mem *)stream;
    int32_t new_size = size;
    uint8_t *new_buf = NULL;


    new_buf = (uint8_t *)MZ_ALLOC((uint32_t)new_size);
    if (new_buf == NULL)
        return MZ_BUF_ERROR;

    if (mem->buffer)
    {
        memcpy(new_buf, mem->buffer, mem->size);
        MZ_FREE(mem->buffer);
    }

    mem->buffer = new_buf;
    mem->size = new_size;
    return MZ_OK;
}
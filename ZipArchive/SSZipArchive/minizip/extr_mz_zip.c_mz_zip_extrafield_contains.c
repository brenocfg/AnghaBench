#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  mz_stream_mem_create (void**) ; 
 int /*<<< orphan*/  mz_stream_mem_delete (void**) ; 
 int /*<<< orphan*/  mz_stream_mem_set_buffer (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_zip_extrafield_find (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int32_t mz_zip_extrafield_contains(const uint8_t *extrafield, int32_t extrafield_size,
    uint16_t type, uint16_t *length)
{
    void *file_extra_stream = NULL;
    int32_t err = MZ_OK;

    if (extrafield == NULL || extrafield_size == 0)
        return MZ_PARAM_ERROR;

    mz_stream_mem_create(&file_extra_stream);
    mz_stream_mem_set_buffer(file_extra_stream, (void *)extrafield, extrafield_size);

    err = mz_zip_extrafield_find(file_extra_stream, type, length);

    mz_stream_mem_delete(&file_extra_stream);

    return err;
}
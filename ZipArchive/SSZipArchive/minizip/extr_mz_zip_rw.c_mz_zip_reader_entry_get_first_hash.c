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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {TYPE_1__* file_info; } ;
typedef  TYPE_2__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  extrafield_size; scalar_t__ extrafield; } ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  MZ_ZIP_EXTENSION_HASH ; 
 int /*<<< orphan*/  mz_stream_mem_create (void**) ; 
 int /*<<< orphan*/  mz_stream_mem_delete (void**) ; 
 int /*<<< orphan*/  mz_stream_mem_set_buffer (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_stream_read_uint16 (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ mz_zip_extrafield_find (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int32_t mz_zip_reader_entry_get_first_hash(void *handle, uint16_t *algorithm, uint16_t *digest_size)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    void *file_extra_stream = NULL;
    int32_t err = MZ_OK;
    uint16_t cur_algorithm = 0;
    uint16_t cur_digest_size = 0;

    if (reader == NULL || algorithm == NULL)
        return MZ_PARAM_ERROR;

    mz_stream_mem_create(&file_extra_stream);
    mz_stream_mem_set_buffer(file_extra_stream, (void *)reader->file_info->extrafield,
        reader->file_info->extrafield_size);

    err = mz_zip_extrafield_find(file_extra_stream, MZ_ZIP_EXTENSION_HASH, NULL);
    if (err == MZ_OK)
        err = mz_stream_read_uint16(file_extra_stream, &cur_algorithm);
    if (err == MZ_OK)
        err = mz_stream_read_uint16(file_extra_stream, &cur_digest_size);

    if (algorithm != NULL)
        *algorithm = cur_algorithm;
    if (digest_size != NULL)
        *digest_size = cur_digest_size;

    mz_stream_mem_delete(&file_extra_stream);

    return err;
}
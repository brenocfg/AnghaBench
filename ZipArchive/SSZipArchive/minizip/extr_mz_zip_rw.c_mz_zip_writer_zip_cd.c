#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/ * password; int /*<<< orphan*/  compress_method; int /*<<< orphan*/  zip_handle; } ;
typedef  TYPE_1__ mz_zip_writer ;
struct TYPE_7__ {scalar_t__ extrafield_size; int /*<<< orphan*/  extrafield; int /*<<< orphan*/  flag; scalar_t__ uncompressed_size; int /*<<< orphan*/  compression_method; int /*<<< orphan*/  version_madeby; int /*<<< orphan*/  modified_date; int /*<<< orphan*/  filename; } ;
typedef  TYPE_2__ mz_zip_file ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  cd_file ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_CREATE ; 
 int /*<<< orphan*/  MZ_SEEK_END ; 
 int /*<<< orphan*/  MZ_SEEK_SET ; 
 int /*<<< orphan*/  MZ_VERSION_MADEBY ; 
 int /*<<< orphan*/  MZ_ZIP_CD_FILENAME ; 
 int /*<<< orphan*/  MZ_ZIP_EXTENSION_CDCD ; 
 int /*<<< orphan*/  MZ_ZIP_FLAG_ENCRYPTED ; 
 int /*<<< orphan*/  MZ_ZIP_FLAG_UTF8 ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mz_stream_copy_stream (void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mz_stream_mem_create (void**) ; 
 int /*<<< orphan*/  mz_stream_mem_delete (void**) ; 
 int /*<<< orphan*/  mz_stream_mem_get_buffer (void*,void const**) ; 
 int /*<<< orphan*/  mz_stream_mem_get_buffer_length (void*,scalar_t__*) ; 
 int /*<<< orphan*/  mz_stream_mem_open (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_mem_set_buffer_limit (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_seek (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_stream_tell (void*) ; 
 int /*<<< orphan*/  mz_stream_write_uint64 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_zip_extrafield_write (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mz_zip_get_cd_mem_stream (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  mz_zip_get_number_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mz_zip_writer_entry_close (TYPE_1__*) ; 
 scalar_t__ mz_zip_writer_entry_open (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  mz_zip_writer_entry_write ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int32_t mz_zip_writer_zip_cd(void *handle)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    mz_zip_file cd_file;
    uint64_t number_entry = 0;
    int64_t cd_mem_length = 0;
    int32_t err = MZ_OK;
    int32_t extrafield_size = 0;
    void *file_extra_stream = NULL;
    void *cd_mem_stream = NULL;


    memset(&cd_file, 0, sizeof(cd_file));

    mz_zip_get_number_entry(writer->zip_handle, &number_entry);
    mz_zip_get_cd_mem_stream(writer->zip_handle, &cd_mem_stream);
    mz_stream_seek(cd_mem_stream, 0, MZ_SEEK_END);
    cd_mem_length = (uint32_t)mz_stream_tell(cd_mem_stream);
    mz_stream_seek(cd_mem_stream, 0, MZ_SEEK_SET);

    cd_file.filename = MZ_ZIP_CD_FILENAME;
    cd_file.modified_date = time(NULL);
    cd_file.version_madeby = MZ_VERSION_MADEBY;
    cd_file.compression_method = writer->compress_method;
    cd_file.uncompressed_size = (int32_t)cd_mem_length;
    cd_file.flag = MZ_ZIP_FLAG_UTF8;

    if (writer->password != NULL)
        cd_file.flag |= MZ_ZIP_FLAG_ENCRYPTED;

    mz_stream_mem_create(&file_extra_stream);
    mz_stream_mem_open(file_extra_stream, NULL, MZ_OPEN_MODE_CREATE);

    mz_zip_extrafield_write(file_extra_stream, MZ_ZIP_EXTENSION_CDCD, 8);

    mz_stream_write_uint64(file_extra_stream, number_entry);

    mz_stream_mem_get_buffer(file_extra_stream, (const void **)&cd_file.extrafield);
    mz_stream_mem_get_buffer_length(file_extra_stream, &extrafield_size);
    cd_file.extrafield_size = (uint16_t)extrafield_size;

    err = mz_zip_writer_entry_open(handle, &cd_file);
    if (err == MZ_OK)
    {
        mz_stream_copy_stream(handle, mz_zip_writer_entry_write, cd_mem_stream,
            NULL, (int32_t)cd_mem_length);

        mz_stream_seek(cd_mem_stream, 0, MZ_SEEK_SET);
        mz_stream_mem_set_buffer_limit(cd_mem_stream, 0);

        err = mz_zip_writer_entry_close(writer);
    }

    mz_stream_mem_delete(&file_extra_stream);

    return err;
}
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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sha256 ;
struct TYPE_3__ {scalar_t__ extrafield_size; int /*<<< orphan*/  crc; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/ * extrafield; int /*<<< orphan*/  filename; } ;
struct TYPE_4__ {scalar_t__ cert_data_size; int /*<<< orphan*/  zip_handle; TYPE_1__ file_info; scalar_t__ raw; int /*<<< orphan*/  file_extra_stream; int /*<<< orphan*/  cert_pwd; int /*<<< orphan*/ * cert_data; int /*<<< orphan*/  zip_cd; int /*<<< orphan*/ * sha256; } ;
typedef  TYPE_2__ mz_zip_writer ;
typedef  scalar_t__ int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int MZ_HASH_SHA256 ; 
 int MZ_HASH_SHA256_SIZE ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_CREATE ; 
 scalar_t__ MZ_WRITE_ERROR ; 
 int /*<<< orphan*/  MZ_ZIP_CD_FILENAME ; 
 int /*<<< orphan*/  MZ_ZIP_EXTENSION_HASH ; 
 int /*<<< orphan*/  mz_crypt_sha_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_crypt_sha_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mz_stream_mem_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_mem_get_buffer (int /*<<< orphan*/ ,void const**) ; 
 int /*<<< orphan*/  mz_stream_mem_get_buffer_length (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mz_stream_mem_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_mem_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int mz_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mz_stream_write_uint16 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mz_zip_entry_close (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_entry_close_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_zip_entry_set_extrafield (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_extrafield_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mz_zip_writer_entry_sign (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t mz_zip_writer_entry_close(void *handle)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    int32_t err = MZ_OK;
#ifndef MZ_ZIP_NO_ENCRYPTION
    const uint8_t *extrafield = NULL;
    int32_t extrafield_size = 0;
    int16_t field_length_hash = 0;
    uint8_t sha256[MZ_HASH_SHA256_SIZE];


    if (writer->sha256 != NULL)
    {
        mz_crypt_sha_end(writer->sha256, sha256, sizeof(sha256));
        mz_crypt_sha_delete(&writer->sha256);

        /* Copy extrafield so we can append our own fields before close */
        mz_stream_mem_create(&writer->file_extra_stream);
        mz_stream_mem_open(writer->file_extra_stream, NULL, MZ_OPEN_MODE_CREATE);

        /* Write sha256 hash to extrafield */
        field_length_hash = 4 + MZ_HASH_SHA256_SIZE;
        err = mz_zip_extrafield_write(writer->file_extra_stream, MZ_ZIP_EXTENSION_HASH, field_length_hash);
        if (err == MZ_OK)
            err = mz_stream_write_uint16(writer->file_extra_stream, MZ_HASH_SHA256);
        if (err == MZ_OK)
            err = mz_stream_write_uint16(writer->file_extra_stream, MZ_HASH_SHA256_SIZE);
        if (err == MZ_OK)
        {
            if (mz_stream_write(writer->file_extra_stream, sha256, sizeof(sha256)) != MZ_HASH_SHA256_SIZE)
                err = MZ_WRITE_ERROR;
        }

#ifdef MZ_ZIP_SIGNING
        if ((err == MZ_OK) && (writer->cert_data != NULL) && (writer->cert_data_size > 0))
        {
            /* Sign entry if not zipping cd or if it is cd being zipped */
            if (!writer->zip_cd || strcmp(writer->file_info.filename, MZ_ZIP_CD_FILENAME) == 0)
            {
                err = mz_zip_writer_entry_sign(handle, sha256, sizeof(sha256),
                    writer->cert_data, writer->cert_data_size, writer->cert_pwd);
            }
        }
#endif

        if ((writer->file_info.extrafield != NULL) && (writer->file_info.extrafield_size > 0))
            mz_stream_mem_write(writer->file_extra_stream, writer->file_info.extrafield,
                writer->file_info.extrafield_size);

        /* Update extra field for central directory after adding extra fields */
        mz_stream_mem_get_buffer(writer->file_extra_stream, (const void **)&extrafield);
        mz_stream_mem_get_buffer_length(writer->file_extra_stream, &extrafield_size);

        mz_zip_entry_set_extrafield(writer->zip_handle, extrafield, (uint16_t)extrafield_size);
    }
#endif

    if (err == MZ_OK)
    {
        if (writer->raw)
            err = mz_zip_entry_close_raw(writer->zip_handle, writer->file_info.uncompressed_size,
                writer->file_info.crc);
        else
            err = mz_zip_entry_close(writer->zip_handle);
    }

    return err;
}
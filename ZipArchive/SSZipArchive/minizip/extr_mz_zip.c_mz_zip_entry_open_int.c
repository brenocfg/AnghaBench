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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int compression_method; int flag; int crc; scalar_t__ uncompressed_size; scalar_t__ compressed_size; int /*<<< orphan*/  modified_date; int /*<<< orphan*/  aes_encryption_mode; scalar_t__ aes_version; } ;
struct TYPE_4__ {int entry_raw; int open_mode; int entry_opened; scalar_t__ entry_crc32; int /*<<< orphan*/ * compress_stream; int /*<<< orphan*/ * crypt_stream; TYPE_1__ file_info; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ mz_zip ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
#define  MZ_COMPRESS_METHOD_BZIP2 131 
#define  MZ_COMPRESS_METHOD_DEFLATE 130 
#define  MZ_COMPRESS_METHOD_LZMA 129 
#define  MZ_COMPRESS_METHOD_STORE 128 
 scalar_t__ MZ_OK ; 
 int MZ_OPEN_MODE_READ ; 
 int MZ_OPEN_MODE_WRITE ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  MZ_STREAM_PROP_COMPRESS_LEVEL ; 
 int /*<<< orphan*/  MZ_STREAM_PROP_FOOTER_SIZE ; 
 int /*<<< orphan*/  MZ_STREAM_PROP_HEADER_SIZE ; 
 int /*<<< orphan*/  MZ_STREAM_PROP_TOTAL_IN_MAX ; 
 int /*<<< orphan*/  MZ_STREAM_PROP_TOTAL_OUT_MAX ; 
 scalar_t__ MZ_SUPPORT_ERROR ; 
 int MZ_ZIP_FLAG_DATA_DESCRIPTOR ; 
 int MZ_ZIP_FLAG_ENCRYPTED ; 
 int MZ_ZIP_FLAG_LZMA_EOS_MARKER ; 
 int /*<<< orphan*/  mz_stream_bzip_create (int /*<<< orphan*/ **) ; 
 scalar_t__ mz_stream_get_prop_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mz_stream_lzma_create (int /*<<< orphan*/ **) ; 
 scalar_t__ mz_stream_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mz_stream_pkcrypt_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_pkcrypt_set_password (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mz_stream_pkcrypt_set_verify (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mz_stream_raw_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_set_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_set_prop_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mz_stream_wzaes_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_wzaes_set_encryption_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_wzaes_set_password (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mz_stream_zlib_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_zip_entry_close_int (void*) ; 
 int mz_zip_time_t_to_dos_date (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t mz_zip_entry_open_int(void *handle, uint8_t raw, int16_t compress_level, const char *password)
{
    mz_zip *zip = (mz_zip *)handle;
    int64_t max_total_in = 0;
    int64_t header_size = 0;
    int64_t footer_size = 0;
    int32_t err = MZ_OK;
    uint8_t use_crypt = 0;

    if (zip == NULL)
        return MZ_PARAM_ERROR;

    switch (zip->file_info.compression_method)
    {
    case MZ_COMPRESS_METHOD_STORE:
    case MZ_COMPRESS_METHOD_DEFLATE:
#ifdef HAVE_BZIP2
    case MZ_COMPRESS_METHOD_BZIP2:
#endif
#ifdef HAVE_LZMA
    case MZ_COMPRESS_METHOD_LZMA:
#endif
        err = MZ_OK;
        break;
    default:
        return MZ_SUPPORT_ERROR;
    }

#ifndef HAVE_WZAES
    if (zip->file_info.aes_version)
        return MZ_SUPPORT_ERROR;
#endif

    zip->entry_raw = raw;

    if ((zip->file_info.flag & MZ_ZIP_FLAG_ENCRYPTED) && (password != NULL))
    {
        if (zip->open_mode & MZ_OPEN_MODE_WRITE)
        {
            /* Encrypt only when we are not trying to write raw and password is supplied. */
            if (!zip->entry_raw)
                use_crypt = 1;
        }
        else if (zip->open_mode & MZ_OPEN_MODE_READ)
        {
            /* Decrypt only when password is supplied. Don't error when password */
            /* is not supplied as we may want to read the raw encrypted data. */
            use_crypt = 1;
        }
    }

    if ((err == MZ_OK) && (use_crypt))
    {
#ifdef HAVE_WZAES
        if (zip->file_info.aes_version)
        {
            mz_stream_wzaes_create(&zip->crypt_stream);
            mz_stream_wzaes_set_password(zip->crypt_stream, password);
            mz_stream_wzaes_set_encryption_mode(zip->crypt_stream, zip->file_info.aes_encryption_mode);
        }
        else
#endif
        {
#ifdef HAVE_PKCRYPT
            uint8_t verify1 = 0;
            uint8_t verify2 = 0;

            /* Info-ZIP modification to ZipCrypto format: */
            /* If bit 3 of the general purpose bit flag is set, it uses high byte of 16-bit File Time. */

            if (zip->file_info.flag & MZ_ZIP_FLAG_DATA_DESCRIPTOR)
            {
                uint32_t dos_date = 0;

                dos_date = mz_zip_time_t_to_dos_date(zip->file_info.modified_date);

                verify1 = (uint8_t)((dos_date >> 16) & 0xff);
                verify2 = (uint8_t)((dos_date >> 8) & 0xff);
            }
            else
            {
                verify1 = (uint8_t)((zip->file_info.crc >> 16) & 0xff);
                verify2 = (uint8_t)((zip->file_info.crc >> 24) & 0xff);
            }

            mz_stream_pkcrypt_create(&zip->crypt_stream);
            mz_stream_pkcrypt_set_password(zip->crypt_stream, password);
            mz_stream_pkcrypt_set_verify(zip->crypt_stream, verify1, verify2);
#endif
        }
    }

    if (err == MZ_OK)
    {
        if (zip->crypt_stream == NULL)
            mz_stream_raw_create(&zip->crypt_stream);

        mz_stream_set_base(zip->crypt_stream, zip->stream);

        err = mz_stream_open(zip->crypt_stream, NULL, zip->open_mode);
    }

    if (err == MZ_OK)
    {
        if (zip->entry_raw || zip->file_info.compression_method == MZ_COMPRESS_METHOD_STORE)
            mz_stream_raw_create(&zip->compress_stream);
#if defined(HAVE_ZLIB) || defined(HAVE_LIBCOMP)
        else if (zip->file_info.compression_method == MZ_COMPRESS_METHOD_DEFLATE)
            mz_stream_zlib_create(&zip->compress_stream);
#endif
#ifdef HAVE_BZIP2
        else if (zip->file_info.compression_method == MZ_COMPRESS_METHOD_BZIP2)
            mz_stream_bzip_create(&zip->compress_stream);
#endif
#ifdef HAVE_LZMA
        else if (zip->file_info.compression_method == MZ_COMPRESS_METHOD_LZMA)
            mz_stream_lzma_create(&zip->compress_stream);
#endif
        else
            err = MZ_PARAM_ERROR;
    }

    if (err == MZ_OK)
    {
        if (zip->open_mode & MZ_OPEN_MODE_WRITE)
        {
            mz_stream_set_prop_int64(zip->compress_stream, MZ_STREAM_PROP_COMPRESS_LEVEL, compress_level);
        }
        else
        {
#ifndef HAVE_LIBCOMP
            if (zip->entry_raw || zip->file_info.compression_method == MZ_COMPRESS_METHOD_STORE || zip->file_info.flag & MZ_ZIP_FLAG_ENCRYPTED)
#endif
            {
                max_total_in = zip->file_info.compressed_size;
                mz_stream_set_prop_int64(zip->crypt_stream, MZ_STREAM_PROP_TOTAL_IN_MAX, max_total_in);

                if (mz_stream_get_prop_int64(zip->crypt_stream, MZ_STREAM_PROP_HEADER_SIZE, &header_size) == MZ_OK)
                    max_total_in -= header_size;
                if (mz_stream_get_prop_int64(zip->crypt_stream, MZ_STREAM_PROP_FOOTER_SIZE, &footer_size) == MZ_OK)
                    max_total_in -= footer_size;

                mz_stream_set_prop_int64(zip->compress_stream, MZ_STREAM_PROP_TOTAL_IN_MAX, max_total_in);
            }
            if ((zip->file_info.compression_method == MZ_COMPRESS_METHOD_LZMA) && (zip->file_info.flag & MZ_ZIP_FLAG_LZMA_EOS_MARKER) == 0)
            {
                mz_stream_set_prop_int64(zip->compress_stream, MZ_STREAM_PROP_TOTAL_IN_MAX, zip->file_info.compressed_size);
                mz_stream_set_prop_int64(zip->compress_stream, MZ_STREAM_PROP_TOTAL_OUT_MAX, zip->file_info.uncompressed_size);
            }
        }

        mz_stream_set_base(zip->compress_stream, zip->crypt_stream);

        err = mz_stream_open(zip->compress_stream, NULL, zip->open_mode);
    }

    if (err == MZ_OK)
    {
        zip->entry_opened = 1;
        zip->entry_crc32 = 0;
    }
    else
    {
        mz_zip_entry_close_int(handle);
    }

    return err;
}
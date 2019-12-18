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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_ZIP_MAGIC_DATADESCRIPTOR ; 
 scalar_t__ mz_stream_write_int64 (void*,scalar_t__) ; 
 scalar_t__ mz_stream_write_uint32 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t mz_zip_entry_write_descriptor(void *stream, uint8_t zip64, uint32_t crc32, int64_t compressed_size, int64_t uncompressed_size)
{
    int32_t err = MZ_OK;

    err = mz_stream_write_uint32(stream, MZ_ZIP_MAGIC_DATADESCRIPTOR);
    if (err == MZ_OK)
        err = mz_stream_write_uint32(stream, crc32);

    /* Store data descriptor as 8 bytes if zip 64 extension enabled */
    if (err == MZ_OK)
    {
        /* Zip 64 extension is enabled when uncompressed size is > UINT32_MAX */
        if (!zip64)
            err = mz_stream_write_uint32(stream, (uint32_t)compressed_size);
        else
            err = mz_stream_write_int64(stream, compressed_size);
    }
    if (err == MZ_OK)
    {
        if (!zip64)
            err = mz_stream_write_uint32(stream, (uint32_t)uncompressed_size);
        else
            err = mz_stream_write_int64(stream, uncompressed_size);
    }

    return err;
}
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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int initialized; char* password; scalar_t__ verify1; scalar_t__ verify2; scalar_t__ total_in; TYPE_1__ stream; scalar_t__ total_out; } ;
typedef  TYPE_2__ mz_stream_pkcrypt ;
typedef  int int32_t ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int MZ_OPEN_ERROR ; 
 int MZ_OPEN_MODE_READ ; 
 int MZ_OPEN_MODE_WRITE ; 
 int MZ_PARAM_ERROR ; 
 int MZ_PASSWORD_ERROR ; 
 int MZ_PKCRYPT_HEADER_SIZE ; 
 int MZ_READ_ERROR ; 
 int MZ_SUPPORT_ERROR ; 
 int /*<<< orphan*/  MZ_UNUSED (scalar_t__) ; 
 int MZ_WRITE_ERROR ; 
 int /*<<< orphan*/  mz_crypt_rand (scalar_t__*,int) ; 
 scalar_t__ mz_stream_is_open (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_stream_pkcrypt_decode (void*,scalar_t__) ; 
 scalar_t__ mz_stream_pkcrypt_encode (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mz_stream_pkcrypt_init_keys (void*,char const*) ; 
 int mz_stream_read (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int mz_stream_write (int /*<<< orphan*/ ,scalar_t__*,int) ; 

int32_t mz_stream_pkcrypt_open(void *stream, const char *path, int32_t mode)
{
    mz_stream_pkcrypt *pkcrypt = (mz_stream_pkcrypt *)stream;
    uint16_t t = 0;
    int16_t i = 0;
    uint8_t verify1 = 0;
    uint8_t verify2 = 0;
    uint8_t header[MZ_PKCRYPT_HEADER_SIZE];
    const char *password = path;

    pkcrypt->total_in = 0;
    pkcrypt->total_out = 0;
    pkcrypt->initialized = 0;

    if (mz_stream_is_open(pkcrypt->stream.base) != MZ_OK)
        return MZ_OPEN_ERROR;

    if (password == NULL)
        password = pkcrypt->password;
    if (password == NULL)
        return MZ_PARAM_ERROR;

    mz_stream_pkcrypt_init_keys(stream, password);

    if (mode & MZ_OPEN_MODE_WRITE)
    {
#ifdef MZ_ZIP_NO_COMPRESSION
        MZ_UNUSED(t);
        MZ_UNUSED(i);

        return MZ_SUPPORT_ERROR;
#else
        /* First generate RAND_HEAD_LEN - 2 random bytes. */
        mz_crypt_rand(header, MZ_PKCRYPT_HEADER_SIZE - 2);

        /* Encrypt random header (last two bytes is high word of crc) */
        for (i = 0; i < MZ_PKCRYPT_HEADER_SIZE - 2; i++)
            header[i] = mz_stream_pkcrypt_encode(stream, header[i], t);

        header[i++] = mz_stream_pkcrypt_encode(stream, pkcrypt->verify1, t);
        header[i++] = mz_stream_pkcrypt_encode(stream, pkcrypt->verify2, t);

        if (mz_stream_write(pkcrypt->stream.base, header, sizeof(header)) != sizeof(header))
            return MZ_WRITE_ERROR;

        pkcrypt->total_out += MZ_PKCRYPT_HEADER_SIZE;
#endif
    }
    else if (mode & MZ_OPEN_MODE_READ)
    {
#ifdef MZ_ZIP_NO_DECOMPRESSION
        MZ_UNUSED(t);
        MZ_UNUSED(i);
        MZ_UNUSED(verify1);
        MZ_UNUSED(verify2);

        return MZ_SUPPORT_ERROR;
#else
        if (mz_stream_read(pkcrypt->stream.base, header, sizeof(header)) != sizeof(header))
            return MZ_READ_ERROR;

        for (i = 0; i < MZ_PKCRYPT_HEADER_SIZE - 2; i++)
            header[i] = mz_stream_pkcrypt_decode(stream, header[i]);

        verify1 = mz_stream_pkcrypt_decode(stream, header[i++]);
        verify2 = mz_stream_pkcrypt_decode(stream, header[i++]);

        /* Older versions used 2 byte check, newer versions use 1 byte check. */
        MZ_UNUSED(verify1);
        if ((verify2 != 0) && (verify2 != pkcrypt->verify2))
            return MZ_PASSWORD_ERROR;

        pkcrypt->total_in += MZ_PKCRYPT_HEADER_SIZE;
#endif
    }

    pkcrypt->initialized = 1;
    return MZ_OK;
}
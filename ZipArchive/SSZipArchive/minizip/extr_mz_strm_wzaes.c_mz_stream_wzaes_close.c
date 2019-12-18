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
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int mode; scalar_t__ initialized; int /*<<< orphan*/  total_in; TYPE_1__ stream; int /*<<< orphan*/  total_out; int /*<<< orphan*/  hmac; } ;
typedef  TYPE_2__ mz_stream_wzaes ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  computed_hash ;

/* Variables and functions */
 int MZ_AES_AUTHCODE_SIZE ; 
 int /*<<< orphan*/  MZ_CRC_ERROR ; 
 int MZ_HASH_SHA1_SIZE ; 
 int /*<<< orphan*/  MZ_OK ; 
 int MZ_OPEN_MODE_READ ; 
 int MZ_OPEN_MODE_WRITE ; 
 int /*<<< orphan*/  MZ_READ_ERROR ; 
 int /*<<< orphan*/  MZ_WRITE_ERROR ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mz_crypt_hmac_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mz_stream_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mz_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int32_t mz_stream_wzaes_close(void *stream)
{
    mz_stream_wzaes *wzaes = (mz_stream_wzaes *)stream;
    uint8_t expected_hash[MZ_AES_AUTHCODE_SIZE];
    uint8_t computed_hash[MZ_HASH_SHA1_SIZE];

    mz_crypt_hmac_end(wzaes->hmac, computed_hash, sizeof(computed_hash));

    if (wzaes->mode & MZ_OPEN_MODE_WRITE)
    {
        if (mz_stream_write(wzaes->stream.base, computed_hash, MZ_AES_AUTHCODE_SIZE) != MZ_AES_AUTHCODE_SIZE)
            return MZ_WRITE_ERROR;

        wzaes->total_out += MZ_AES_AUTHCODE_SIZE;
    }
    else if (wzaes->mode & MZ_OPEN_MODE_READ)
    {
        if (mz_stream_read(wzaes->stream.base, expected_hash, MZ_AES_AUTHCODE_SIZE) != MZ_AES_AUTHCODE_SIZE)
            return MZ_READ_ERROR;

        wzaes->total_in += MZ_AES_AUTHCODE_SIZE;

        /* If entire entry was not read this will fail */
        if (memcmp(computed_hash, expected_hash, MZ_AES_AUTHCODE_SIZE) != 0)
            return MZ_CRC_ERROR;
    }

    wzaes->initialized = 0;
    return MZ_OK;
}
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
struct TYPE_2__ {int /*<<< orphan*/  zip_handle; int /*<<< orphan*/  hash_digest_size; int /*<<< orphan*/  hash_algorithm; int /*<<< orphan*/ * hash; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  computed_hash ;

/* Variables and functions */
 scalar_t__ MZ_CRC_ERROR ; 
 int MZ_HASH_MAX_SIZE ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_crypt_sha_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_crypt_sha_end (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mz_zip_entry_close (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_reader_entry_get_hash (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int32_t mz_zip_reader_entry_close(void *handle)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    int32_t err = MZ_OK;
    int32_t err_close = MZ_OK;
#ifndef MZ_ZIP_NO_ENCRYPTION
    int32_t err_hash = MZ_OK;
    uint8_t computed_hash[MZ_HASH_MAX_SIZE];
    uint8_t expected_hash[MZ_HASH_MAX_SIZE];

    if (reader->hash != NULL)
    {
        mz_crypt_sha_end(reader->hash, computed_hash, sizeof(computed_hash));
        mz_crypt_sha_delete(&reader->hash);

        err_hash = mz_zip_reader_entry_get_hash(handle, reader->hash_algorithm, expected_hash,
            reader->hash_digest_size);

        if (err_hash == MZ_OK)
        {
            /* Verify expected hash against computed hash */
            if (memcmp(computed_hash, expected_hash, reader->hash_digest_size) != 0)
                err = MZ_CRC_ERROR;
        }
    }
#endif

    err_close = mz_zip_entry_close(reader->zip_handle);
    if (err == MZ_OK)
        err = err_close;
    return err;
}
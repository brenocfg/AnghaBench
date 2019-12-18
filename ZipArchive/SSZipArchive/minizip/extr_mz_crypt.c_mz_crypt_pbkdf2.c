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
typedef  int /*<<< orphan*/  ux ;
typedef  int /*<<< orphan*/  uu ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_HASH_SHA1 ; 
 int MZ_HASH_SHA1_SIZE ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mz_crypt_hmac_copy (void*,void*) ; 
 int /*<<< orphan*/  mz_crypt_hmac_create (void**) ; 
 int /*<<< orphan*/  mz_crypt_hmac_delete (void**) ; 
 scalar_t__ mz_crypt_hmac_end (void*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mz_crypt_hmac_init (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mz_crypt_hmac_set_algorithm (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_crypt_hmac_update (void*,int /*<<< orphan*/ *,int) ; 

int32_t  mz_crypt_pbkdf2(uint8_t *password, int32_t password_length, uint8_t *salt,
    int32_t salt_length, int32_t iteration_count, uint8_t *key, int32_t key_length)
{
    void *hmac1 = NULL;
    void *hmac2 = NULL;
    void *hmac3 = NULL;
    int32_t err = MZ_OK;
    uint16_t i = 0;
    uint16_t j = 0;
    uint16_t k = 0;
    uint16_t block_count = 0;
    uint8_t uu[MZ_HASH_SHA1_SIZE];
    uint8_t ux[MZ_HASH_SHA1_SIZE];

    if (password == NULL || salt == NULL || key == NULL)
        return MZ_PARAM_ERROR;

    memset(key, 0, key_length);

    mz_crypt_hmac_create(&hmac1);
    mz_crypt_hmac_create(&hmac2);
    mz_crypt_hmac_create(&hmac3);

    mz_crypt_hmac_set_algorithm(hmac1, MZ_HASH_SHA1);
    mz_crypt_hmac_set_algorithm(hmac2, MZ_HASH_SHA1);
    mz_crypt_hmac_set_algorithm(hmac3, MZ_HASH_SHA1);

    err = mz_crypt_hmac_init(hmac1, password, password_length);
    if (err == MZ_OK)
        err = mz_crypt_hmac_init(hmac2, password, password_length);
    if (err == MZ_OK)
        err = mz_crypt_hmac_update(hmac2, salt, salt_length);

    block_count = 1 + ((uint16_t)key_length - 1) / MZ_HASH_SHA1_SIZE;

    for (i = 0; (err == MZ_OK) && (i < block_count); i += 1)
    {
        memset(ux, 0, sizeof(ux));

        err = mz_crypt_hmac_copy(hmac2, hmac3);
        if (err != MZ_OK)
            break;

        uu[0] = (uint8_t)((i + 1) >> 24);
        uu[1] = (uint8_t)((i + 1) >> 16);
        uu[2] = (uint8_t)((i + 1) >> 8);
        uu[3] = (uint8_t)(i + 1);

        for (j = 0, k = 4; j < iteration_count; j += 1)
        {
            err = mz_crypt_hmac_update(hmac3, uu, k);
            if (err == MZ_OK)
                err = mz_crypt_hmac_end(hmac3, uu, sizeof(uu));
            if (err != MZ_OK)
                break;

            for(k = 0; k < MZ_HASH_SHA1_SIZE; k += 1)
                ux[k] ^= uu[k];

            err = mz_crypt_hmac_copy(hmac1, hmac3);
            if (err != MZ_OK)
                break;
        }

        if (err != MZ_OK)
            break;

        j = 0;
        k = i * MZ_HASH_SHA1_SIZE;

        while (j < MZ_HASH_SHA1_SIZE && k < key_length)
            key[k++] = ux[j++];
    }

    /* hmac3 uses the same provider as hmac2, so it must be deleted
       before the context is destroyed. */
    mz_crypt_hmac_delete(&hmac3);
    mz_crypt_hmac_delete(&hmac1);
    mz_crypt_hmac_delete(&hmac2);

    return err;
}
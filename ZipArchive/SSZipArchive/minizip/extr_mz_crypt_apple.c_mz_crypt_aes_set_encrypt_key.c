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
struct TYPE_2__ {scalar_t__ error; int /*<<< orphan*/  crypt; } ;
typedef  TYPE_1__ mz_crypt_aes ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ CCCryptorCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MZ_HASH_ERROR ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  kCCAlgorithmAES ; 
 int /*<<< orphan*/  kCCEncrypt ; 
 int /*<<< orphan*/  kCCOptionECBMode ; 
 scalar_t__ kCCSuccess ; 
 int /*<<< orphan*/  mz_crypt_aes_reset (void*) ; 

int32_t mz_crypt_aes_set_encrypt_key(void *handle, const void *key, int32_t key_length)
{
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;


    if (aes == NULL || key == NULL || key_length == 0)
        return MZ_PARAM_ERROR;

    mz_crypt_aes_reset(handle);

    aes->error = CCCryptorCreate(kCCEncrypt, kCCAlgorithmAES, kCCOptionECBMode,
        key, key_length, NULL, &aes->crypt);

    if (aes->error != kCCSuccess)
        return MZ_HASH_ERROR;

    return MZ_OK;
}
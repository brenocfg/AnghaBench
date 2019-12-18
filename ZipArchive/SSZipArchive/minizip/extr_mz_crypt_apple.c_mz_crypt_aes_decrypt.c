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
struct TYPE_2__ {scalar_t__ error; int /*<<< orphan*/  crypt; } ;
typedef  TYPE_1__ mz_crypt_aes ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ CCCryptorUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  MZ_AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  MZ_HASH_ERROR ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 scalar_t__ kCCSuccess ; 

int32_t mz_crypt_aes_decrypt(void *handle, uint8_t *buf, int32_t size)
{
    mz_crypt_aes *aes = (mz_crypt_aes *)handle;
    size_t data_moved = 0;

    if (aes == NULL || buf == NULL)
        return MZ_PARAM_ERROR;
    if (size != MZ_AES_BLOCK_SIZE)
        return MZ_PARAM_ERROR;

    aes->error = CCCryptorUpdate(aes->crypt, buf, size, buf, size, &data_moved);

    if (aes->error != kCCSuccess)
        return MZ_HASH_ERROR;

    return size;
}
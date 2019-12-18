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
struct TYPE_2__ {scalar_t__ algorithm; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ mz_crypt_hmac ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCHmacFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ MZ_BUF_ERROR ; 
 scalar_t__ MZ_HASH_SHA1 ; 
 scalar_t__ MZ_HASH_SHA1_SIZE ; 
 scalar_t__ MZ_HASH_SHA256_SIZE ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 

int32_t mz_crypt_hmac_end(void *handle, uint8_t *digest, int32_t digest_size)
{
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)handle;

    if (hmac == NULL || digest == NULL)
        return MZ_PARAM_ERROR;

    if (hmac->algorithm == MZ_HASH_SHA1)
    {
        if (digest_size < MZ_HASH_SHA1_SIZE)
            return MZ_BUF_ERROR;
        CCHmacFinal(&hmac->ctx, digest);
    }
    else
    {
        if (digest_size < MZ_HASH_SHA256_SIZE)
            return MZ_BUF_ERROR;
        CCHmacFinal(&hmac->ctx, digest);
    }

    return MZ_OK;
}
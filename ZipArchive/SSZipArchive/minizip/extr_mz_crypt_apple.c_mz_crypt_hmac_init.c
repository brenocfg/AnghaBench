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
struct TYPE_2__ {scalar_t__ algorithm; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ mz_crypt_hmac ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  CCHmacAlgorithm ;

/* Variables and functions */
 int /*<<< orphan*/  CCHmacInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 scalar_t__ MZ_HASH_SHA1 ; 
 scalar_t__ MZ_HASH_SHA256 ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  kCCHmacAlgSHA1 ; 
 int /*<<< orphan*/  kCCHmacAlgSHA256 ; 
 int /*<<< orphan*/  mz_crypt_hmac_reset (void*) ; 

int32_t mz_crypt_hmac_init(void *handle, const void *key, int32_t key_length)
{
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)handle;
    CCHmacAlgorithm algorithm = 0;

    if (hmac == NULL || key == NULL)
        return MZ_PARAM_ERROR;

    mz_crypt_hmac_reset(handle);

    if (hmac->algorithm == MZ_HASH_SHA1)
        algorithm = kCCHmacAlgSHA1;
    else if (hmac->algorithm == MZ_HASH_SHA256)
        algorithm = kCCHmacAlgSHA256;
    else
        return MZ_PARAM_ERROR;

    CCHmacInit(&hmac->ctx, algorithm, key, key_length);
    return MZ_OK;
}
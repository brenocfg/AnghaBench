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
struct TYPE_2__ {scalar_t__ algorithm; int initialized; int /*<<< orphan*/  error; int /*<<< orphan*/  ctx256; int /*<<< orphan*/  ctx1; } ;
typedef  TYPE_1__ mz_crypt_sha ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CC_SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CC_SHA256_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MZ_HASH_ERROR ; 
 scalar_t__ MZ_HASH_SHA1 ; 
 scalar_t__ MZ_HASH_SHA256 ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  mz_crypt_sha_reset (void*) ; 

int32_t mz_crypt_sha_begin(void *handle)
{
    mz_crypt_sha *sha = (mz_crypt_sha *)handle;

    if (sha == NULL)
        return MZ_PARAM_ERROR;

    mz_crypt_sha_reset(handle);

    if (sha->algorithm == MZ_HASH_SHA1)
        sha->error = CC_SHA1_Init(&sha->ctx1);
    else if (sha->algorithm == MZ_HASH_SHA256)
        sha->error = CC_SHA256_Init(&sha->ctx256);
    else
        return MZ_PARAM_ERROR;

    if (!sha->error)
        return MZ_HASH_ERROR;

    sha->initialized = 1;
    return MZ_OK;
}
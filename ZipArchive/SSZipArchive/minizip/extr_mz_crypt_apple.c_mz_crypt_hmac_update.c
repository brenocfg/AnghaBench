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
struct TYPE_2__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ mz_crypt_hmac ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCHmacUpdate (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int32_t mz_crypt_hmac_update(void *handle, const void *buf, int32_t size)
{
    mz_crypt_hmac *hmac = (mz_crypt_hmac *)handle;

    if (hmac == NULL || buf == NULL)
        return MZ_PARAM_ERROR;

    CCHmacUpdate(&hmac->ctx, buf, size);
    return MZ_OK;
}
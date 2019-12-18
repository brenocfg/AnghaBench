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
typedef  int /*<<< orphan*/  mbedtls_sha256_context ;
typedef  int /*<<< orphan*/ * bootloader_sha256_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int mbedtls_sha256_update_ret (int /*<<< orphan*/ *,void const*,size_t) ; 

void bootloader_sha256_data(bootloader_sha256_handle_t handle, const void *data, size_t data_len)
{
    assert(handle != NULL);
    mbedtls_sha256_context *ctx = (mbedtls_sha256_context *)handle;
    int ret = mbedtls_sha256_update_ret(ctx, data, data_len);
    assert(ret == 0);
}
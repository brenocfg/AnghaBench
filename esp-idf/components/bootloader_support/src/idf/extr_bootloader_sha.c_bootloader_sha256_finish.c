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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mbedtls_sha256_context ;
typedef  int /*<<< orphan*/ * bootloader_sha256_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int mbedtls_sha256_finish_ret (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_free (int /*<<< orphan*/ *) ; 

void bootloader_sha256_finish(bootloader_sha256_handle_t handle, uint8_t *digest)
{
    assert(handle != NULL);
    mbedtls_sha256_context *ctx = (mbedtls_sha256_context *)handle;
    if (digest != NULL) {
        int ret = mbedtls_sha256_finish_ret(ctx, digest);
        assert(ret == 0);
    }
    mbedtls_sha256_free(ctx);
    free(handle);
}
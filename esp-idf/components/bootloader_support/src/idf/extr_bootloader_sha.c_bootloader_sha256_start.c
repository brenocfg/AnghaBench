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
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  mbedtls_sha256_init (int /*<<< orphan*/ *) ; 
 int mbedtls_sha256_starts_ret (int /*<<< orphan*/ *,int) ; 

bootloader_sha256_handle_t bootloader_sha256_start(void)
{
    mbedtls_sha256_context *ctx = (mbedtls_sha256_context *)malloc(sizeof(mbedtls_sha256_context));
    if (!ctx) {
        return NULL;
    }
    mbedtls_sha256_init(ctx);
    int ret = mbedtls_sha256_starts_ret(ctx, false);
    if (ret != 0) {
        return NULL;
    }
    return ctx;
}
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
typedef  int /*<<< orphan*/  mbedtls_sha1_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (void*) ; 
 int /*<<< orphan*/  mbedtls_sha1_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sha1_ctx_free( void *ctx )
{
    mbedtls_sha1_free( (mbedtls_sha1_context *) ctx );
    mbedtls_free( ctx );
}
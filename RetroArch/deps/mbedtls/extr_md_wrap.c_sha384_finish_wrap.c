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
typedef  int /*<<< orphan*/  mbedtls_sha512_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_sha512_finish (int /*<<< orphan*/ *,unsigned char*) ; 

__attribute__((used)) static void sha384_finish_wrap( void *ctx, unsigned char *output )
{
    mbedtls_sha512_finish( (mbedtls_sha512_context *) ctx, output );
}
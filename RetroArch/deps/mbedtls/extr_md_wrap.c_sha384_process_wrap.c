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
 int /*<<< orphan*/  mbedtls_sha512_process (int /*<<< orphan*/ *,unsigned char const*) ; 

__attribute__((used)) static void sha384_process_wrap( void *ctx, const unsigned char *data )
{
    mbedtls_sha512_process( (mbedtls_sha512_context *) ctx, data );
}
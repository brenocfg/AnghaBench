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
typedef  int /*<<< orphan*/  mbedtls_arc4_context ;

/* Variables and functions */
 int mbedtls_arc4_crypt (int /*<<< orphan*/ *,size_t,unsigned char const*,unsigned char*) ; 

__attribute__((used)) static int arc4_crypt_stream_wrap( void *ctx, size_t length,
                                   const unsigned char *input,
                                   unsigned char *output )
{
    return( mbedtls_arc4_crypt( (mbedtls_arc4_context *) ctx, length, input, output ) );
}
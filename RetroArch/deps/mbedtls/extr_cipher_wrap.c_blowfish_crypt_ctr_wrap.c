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
typedef  int /*<<< orphan*/  mbedtls_blowfish_context ;

/* Variables and functions */
 int mbedtls_blowfish_crypt_ctr (int /*<<< orphan*/ *,size_t,size_t*,unsigned char*,unsigned char*,unsigned char const*,unsigned char*) ; 

__attribute__((used)) static int blowfish_crypt_ctr_wrap( void *ctx, size_t length, size_t *nc_off,
        unsigned char *nonce_counter, unsigned char *stream_block,
        const unsigned char *input, unsigned char *output )
{
    return mbedtls_blowfish_crypt_ctr( (mbedtls_blowfish_context *) ctx, length, nc_off,
                               nonce_counter, stream_block, input, output );
}
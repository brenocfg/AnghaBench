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
 int MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  mbedtls_arc4_setup (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 

__attribute__((used)) static int arc4_setkey_wrap( void *ctx, const unsigned char *key,
                             unsigned int key_bitlen )
{
    /* we get key_bitlen in bits, arc4 expects it in bytes */
    if( key_bitlen % 8 != 0 )
        return( MBEDTLS_ERR_CIPHER_BAD_INPUT_DATA );

    mbedtls_arc4_setup( (mbedtls_arc4_context *) ctx, key, key_bitlen / 8 );
    return( 0 );
}
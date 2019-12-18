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
struct TYPE_2__ {size_t (* key_len_func ) (int /*<<< orphan*/ ) ;int (* decrypt_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,unsigned char const*,unsigned char*,size_t) ;int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ mbedtls_rsa_alt_context ;

/* Variables and functions */
 int MBEDTLS_ERR_RSA_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_RSA_PRIVATE ; 
 size_t stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,unsigned char const*,unsigned char*,size_t) ; 

__attribute__((used)) static int rsa_alt_decrypt_wrap( void *ctx,
                    const unsigned char *input, size_t ilen,
                    unsigned char *output, size_t *olen, size_t osize,
                    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    mbedtls_rsa_alt_context *rsa_alt = (mbedtls_rsa_alt_context *) ctx;

    ((void) f_rng);
    ((void) p_rng);

    if( ilen != rsa_alt->key_len_func( rsa_alt->key ) )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    return( rsa_alt->decrypt_func( rsa_alt->key,
                MBEDTLS_RSA_PRIVATE, olen, input, output, osize ) );
}
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
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;
typedef  int /*<<< orphan*/  mbedtls_md_context_t ;

/* Variables and functions */
 int MBEDTLS_ERR_MD_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  mbedtls_md_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md_hmac_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md_hmac_starts (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_md_hmac_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_md_init (int /*<<< orphan*/ *) ; 
 int mbedtls_md_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int mbedtls_md_hmac( const mbedtls_md_info_t *md_info, const unsigned char *key, size_t keylen,
                const unsigned char *input, size_t ilen,
                unsigned char *output )
{
    mbedtls_md_context_t ctx;
    int ret;

    if( md_info == NULL )
        return( MBEDTLS_ERR_MD_BAD_INPUT_DATA );

    mbedtls_md_init( &ctx );

    if( ( ret = mbedtls_md_setup( &ctx, md_info, 1 ) ) != 0 )
        return( ret );

    mbedtls_md_hmac_starts( &ctx, key, keylen );
    mbedtls_md_hmac_update( &ctx, input, ilen );
    mbedtls_md_hmac_finish( &ctx, output );

    mbedtls_md_free( &ctx );

    return( 0 );
}
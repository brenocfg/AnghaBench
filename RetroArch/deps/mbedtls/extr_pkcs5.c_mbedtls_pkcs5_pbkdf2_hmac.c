#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  md_info; } ;
typedef  TYPE_1__ mbedtls_md_context_t ;

/* Variables and functions */
 int MBEDTLS_ERR_PKCS5_BAD_INPUT_DATA ; 
 int MBEDTLS_MD_MAX_SIZE ; 
 unsigned char mbedtls_md_get_size (int /*<<< orphan*/ ) ; 
 int mbedtls_md_hmac_finish (TYPE_1__*,unsigned char*) ; 
 int mbedtls_md_hmac_starts (TYPE_1__*,unsigned char const*,size_t) ; 
 int mbedtls_md_hmac_update (TYPE_1__*,unsigned char const*,unsigned char) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

int mbedtls_pkcs5_pbkdf2_hmac( mbedtls_md_context_t *ctx, const unsigned char *password,
                       size_t plen, const unsigned char *salt, size_t slen,
                       unsigned int iteration_count,
                       uint32_t key_length, unsigned char *output )
{
    int ret, j;
    unsigned int i;
    unsigned char md1[MBEDTLS_MD_MAX_SIZE];
    unsigned char work[MBEDTLS_MD_MAX_SIZE];
    unsigned char md_size = mbedtls_md_get_size( ctx->md_info );
    size_t use_len;
    unsigned char *out_p = output;
    unsigned char counter[4];

    memset( counter, 0, 4 );
    counter[3] = 1;

    if( iteration_count > 0xFFFFFFFF )
        return( MBEDTLS_ERR_PKCS5_BAD_INPUT_DATA );

    while( key_length )
    {
        /* U1 ends up in work */
        if( ( ret = mbedtls_md_hmac_starts( ctx, password, plen ) ) != 0 )
            return( ret );

        if( ( ret = mbedtls_md_hmac_update( ctx, salt, slen ) ) != 0 )
            return( ret );

        if( ( ret = mbedtls_md_hmac_update( ctx, counter, 4 ) ) != 0 )
            return( ret );

        if( ( ret = mbedtls_md_hmac_finish( ctx, work ) ) != 0 )
            return( ret );

        memcpy( md1, work, md_size );

        for( i = 1; i < iteration_count; i++ )
        {
            /* U2 ends up in md1 */
            if( ( ret = mbedtls_md_hmac_starts( ctx, password, plen ) ) != 0 )
                return( ret );

            if( ( ret = mbedtls_md_hmac_update( ctx, md1, md_size ) ) != 0 )
                return( ret );

            if( ( ret = mbedtls_md_hmac_finish( ctx, md1 ) ) != 0 )
                return( ret );

            /* U1 xor U2 */
            for( j = 0; j < md_size; j++ )
                work[j] ^= md1[j];
        }

        use_len = ( key_length < md_size ) ? key_length : md_size;
        memcpy( out_p, work, use_len );

        key_length -= (uint32_t) use_len;
        out_p += use_len;

        for( i = 4; i > 0; i-- )
            if( ++counter[i - 1] != 0 )
                break;
    }

    return( 0 );
}
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
struct TYPE_6__ {int /*<<< orphan*/  md_info; } ;
typedef  TYPE_1__ mbedtls_md_context_t ;
typedef  int /*<<< orphan*/  mask ;

/* Variables and functions */
 int MBEDTLS_MD_MAX_SIZE ; 
 int /*<<< orphan*/  mbedtls_md_finish (TYPE_1__*,unsigned char*) ; 
 unsigned int mbedtls_md_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_starts (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_md_update (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_zeroize (unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mgf_mask( unsigned char *dst, size_t dlen, unsigned char *src,
                      size_t slen, mbedtls_md_context_t *md_ctx )
{
    unsigned char mask[MBEDTLS_MD_MAX_SIZE];
    unsigned char counter[4];
    unsigned char *p;
    unsigned int hlen;
    size_t i, use_len;

    memset( mask, 0, MBEDTLS_MD_MAX_SIZE );
    memset( counter, 0, 4 );

    hlen = mbedtls_md_get_size( md_ctx->md_info );

    /* Generate and apply dbMask */
    p = dst;

    while( dlen > 0 )
    {
        use_len = hlen;
        if( dlen < hlen )
            use_len = dlen;

        mbedtls_md_starts( md_ctx );
        mbedtls_md_update( md_ctx, src, slen );
        mbedtls_md_update( md_ctx, counter, 4 );
        mbedtls_md_finish( md_ctx, mask );

        for( i = 0; i < use_len; ++i )
            *p++ ^= mask[i];

        counter[3]++;

        dlen -= use_len;
    }

    mbedtls_zeroize( mask, sizeof( mask ) );
}
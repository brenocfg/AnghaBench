#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* handshake; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_7__ {int /*<<< orphan*/  GY; } ;
struct TYPE_5__ {TYPE_4__ dhm_ctx; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE ; 
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP ; 
 int MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MPI (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 int mbedtls_dhm_read_public (TYPE_4__*,unsigned char*,size_t) ; 

__attribute__((used)) static int ssl_parse_client_dh_public( mbedtls_ssl_context *ssl, unsigned char **p,
                                       const unsigned char *end )
{
    int ret = MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE;
    size_t n;

    /*
     * Receive G^Y mod P, premaster = (G^Y)^X mod P
     */
    if( *p + 2 > end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    n = ( (*p)[0] << 8 ) | (*p)[1];
    *p += 2;

    if( *p + n > end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    if( ( ret = mbedtls_dhm_read_public( &ssl->handshake->dhm_ctx, *p, n ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_read_public", ret );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP );
    }

    *p += n;

    MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: GY", &ssl->handshake->dhm_ctx.GY );

    return( ret );
}
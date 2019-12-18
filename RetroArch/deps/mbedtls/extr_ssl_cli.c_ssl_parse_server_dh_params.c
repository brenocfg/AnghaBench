#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* handshake; TYPE_1__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_9__ {int len; int /*<<< orphan*/  GY; int /*<<< orphan*/  G; int /*<<< orphan*/  P; } ;
struct TYPE_7__ {TYPE_5__ dhm_ctx; } ;
struct TYPE_6__ {int dhm_min_bitlen; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE ; 
 int MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MPI (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 int mbedtls_dhm_read_params (TYPE_5__*,unsigned char**,unsigned char*) ; 

__attribute__((used)) static int ssl_parse_server_dh_params( mbedtls_ssl_context *ssl, unsigned char **p,
                                       unsigned char *end )
{
    int ret = MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE;

    /*
     * Ephemeral DH parameters:
     *
     * struct {
     *     opaque dh_p<1..2^16-1>;
     *     opaque dh_g<1..2^16-1>;
     *     opaque dh_Ys<1..2^16-1>;
     * } ServerDHParams;
     */
    if( ( ret = mbedtls_dhm_read_params( &ssl->handshake->dhm_ctx, p, end ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 2, ( "mbedtls_dhm_read_params" ), ret );
        return( ret );
    }

    if( ssl->handshake->dhm_ctx.len * 8 < ssl->conf->dhm_min_bitlen )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "DHM prime too short: %d < %d",
                                    ssl->handshake->dhm_ctx.len * 8,
                                    ssl->conf->dhm_min_bitlen ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
    }

    MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: P ", &ssl->handshake->dhm_ctx.P  );
    MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: G ", &ssl->handshake->dhm_ctx.G  );
    MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: GY", &ssl->handshake->dhm_ctx.GY );

    return( ret );
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* handshake; } ;
typedef  TYPE_4__ mbedtls_ssl_context ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_5__ mbedtls_ecp_curve_info ;
struct TYPE_10__ {int nbits; int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int /*<<< orphan*/  Qp; TYPE_2__ grp; } ;
struct TYPE_9__ {TYPE_3__ ecdh_ctx; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_ECP (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 TYPE_5__* mbedtls_ecp_curve_info_from_grp_id (int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_ssl_check_curve (TYPE_4__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_check_server_ecdh_params( const mbedtls_ssl_context *ssl )
{
    const mbedtls_ecp_curve_info *curve_info;

    curve_info = mbedtls_ecp_curve_info_from_grp_id( ssl->handshake->ecdh_ctx.grp.id );
    if( curve_info == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "ECDH curve: %s", curve_info->name ) );

#if defined(MBEDTLS_ECP_C)
    if( mbedtls_ssl_check_curve( ssl, ssl->handshake->ecdh_ctx.grp.id ) != 0 )
#else
    if( ssl->handshake->ecdh_ctx.grp.nbits < 163 ||
        ssl->handshake->ecdh_ctx.grp.nbits > 521 )
#endif
        return( -1 );

    MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Qp", &ssl->handshake->ecdh_ctx.Qp );

    return( 0 );
}
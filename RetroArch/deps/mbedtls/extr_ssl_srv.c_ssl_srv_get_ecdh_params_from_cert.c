#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* handshake; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_5__ {int /*<<< orphan*/  ecdh_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ECDH_OURS ; 
 int MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH ; 
 int /*<<< orphan*/  MBEDTLS_PK_ECKEY ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 int mbedtls_ecdh_get_params (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_can_do (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_pk_ec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mbedtls_ssl_own_key (TYPE_2__*) ; 

__attribute__((used)) static int ssl_srv_get_ecdh_params_from_cert( mbedtls_ssl_context *ssl )
{
    int ret;

    if( ! mbedtls_pk_can_do( mbedtls_ssl_own_key( ssl ), MBEDTLS_PK_ECKEY ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "server key not ECDH capable" ) );
        return( MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH );
    }

    if( ( ret = mbedtls_ecdh_get_params( &ssl->handshake->ecdh_ctx,
                                 mbedtls_pk_ec( *mbedtls_ssl_own_key( ssl ) ),
                                 MBEDTLS_ECDH_OURS ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, ( "mbedtls_ecdh_get_params" ), ret );
        return( ret );
    }

    return( 0 );
}
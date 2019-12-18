#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Qp; int /*<<< orphan*/  grp; } ;
typedef  TYPE_1__ mbedtls_ecdh_context ;

/* Variables and functions */
 int mbedtls_ecp_tls_read_group (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 int mbedtls_ecp_tls_read_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const**,int) ; 

int mbedtls_ecdh_read_params( mbedtls_ecdh_context *ctx,
                      const unsigned char **buf, const unsigned char *end )
{
    int ret;

    if( ( ret = mbedtls_ecp_tls_read_group( &ctx->grp, buf, end - *buf ) ) != 0 )
        return( ret );

    if( ( ret = mbedtls_ecp_tls_read_point( &ctx->grp, &ctx->Qp, buf, end - *buf ) )
                != 0 )
        return( ret );

    return( 0 );
}
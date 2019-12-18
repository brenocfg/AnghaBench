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
struct TYPE_3__ {int /*<<< orphan*/  serial; } ;
typedef  TYPE_1__ mbedtls_x509write_cert ;
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int mbedtls_mpi_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int mbedtls_x509write_crt_set_serial( mbedtls_x509write_cert *ctx, const mbedtls_mpi *serial )
{
    int ret;

    if( ( ret = mbedtls_mpi_copy( &ctx->serial, serial ) ) != 0 )
        return( ret );

    return( 0 );
}
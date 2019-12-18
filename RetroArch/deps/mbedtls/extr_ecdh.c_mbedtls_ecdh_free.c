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
struct TYPE_3__ {int /*<<< orphan*/  _d; int /*<<< orphan*/  z; int /*<<< orphan*/  d; int /*<<< orphan*/  Vf; int /*<<< orphan*/  Vi; int /*<<< orphan*/  Qp; int /*<<< orphan*/  Q; int /*<<< orphan*/  grp; } ;
typedef  TYPE_1__ mbedtls_ecdh_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_ecp_group_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 

void mbedtls_ecdh_free( mbedtls_ecdh_context *ctx )
{
    if( ctx == NULL )
        return;

    mbedtls_ecp_group_free( &ctx->grp );
    mbedtls_ecp_point_free( &ctx->Q   );
    mbedtls_ecp_point_free( &ctx->Qp  );
    mbedtls_ecp_point_free( &ctx->Vi  );
    mbedtls_ecp_point_free( &ctx->Vf  );
    mbedtls_mpi_free( &ctx->d  );
    mbedtls_mpi_free( &ctx->z  );
    mbedtls_mpi_free( &ctx->_d );
}
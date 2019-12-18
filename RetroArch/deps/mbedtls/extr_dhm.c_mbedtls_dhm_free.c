#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  P; int /*<<< orphan*/  G; int /*<<< orphan*/  X; int /*<<< orphan*/  GX; int /*<<< orphan*/  GY; int /*<<< orphan*/  K; int /*<<< orphan*/  RP; int /*<<< orphan*/  Vi; int /*<<< orphan*/  Vf; int /*<<< orphan*/  pX; } ;
typedef  TYPE_1__ mbedtls_dhm_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_1__*,int) ; 

void mbedtls_dhm_free( mbedtls_dhm_context *ctx )
{
    mbedtls_mpi_free( &ctx->pX); mbedtls_mpi_free( &ctx->Vf ); mbedtls_mpi_free( &ctx->Vi );
    mbedtls_mpi_free( &ctx->RP ); mbedtls_mpi_free( &ctx->K ); mbedtls_mpi_free( &ctx->GY );
    mbedtls_mpi_free( &ctx->GX ); mbedtls_mpi_free( &ctx->X ); mbedtls_mpi_free( &ctx->G );
    mbedtls_mpi_free( &ctx->P );

    mbedtls_zeroize( ctx, sizeof( mbedtls_dhm_context ) );
}
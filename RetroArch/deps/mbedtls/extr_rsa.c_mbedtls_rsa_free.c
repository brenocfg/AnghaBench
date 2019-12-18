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
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  N; int /*<<< orphan*/  E; int /*<<< orphan*/  D; int /*<<< orphan*/  P; int /*<<< orphan*/  Q; int /*<<< orphan*/  DP; int /*<<< orphan*/  DQ; int /*<<< orphan*/  QP; int /*<<< orphan*/  RN; int /*<<< orphan*/  RP; int /*<<< orphan*/  RQ; int /*<<< orphan*/  Vf; int /*<<< orphan*/  Vi; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mutex_free (int /*<<< orphan*/ *) ; 

void mbedtls_rsa_free( mbedtls_rsa_context *ctx )
{
    mbedtls_mpi_free( &ctx->Vi ); mbedtls_mpi_free( &ctx->Vf );
    mbedtls_mpi_free( &ctx->RQ ); mbedtls_mpi_free( &ctx->RP ); mbedtls_mpi_free( &ctx->RN );
    mbedtls_mpi_free( &ctx->QP ); mbedtls_mpi_free( &ctx->DQ ); mbedtls_mpi_free( &ctx->DP );
    mbedtls_mpi_free( &ctx->Q  ); mbedtls_mpi_free( &ctx->P  ); mbedtls_mpi_free( &ctx->D );
    mbedtls_mpi_free( &ctx->E  ); mbedtls_mpi_free( &ctx->N  );

#if defined(MBEDTLS_THREADING_C)
    mbedtls_mutex_free( &ctx->mutex );
#endif
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hash_id; int /*<<< orphan*/  padding; int /*<<< orphan*/  Vf; int /*<<< orphan*/  Vi; int /*<<< orphan*/  RQ; int /*<<< orphan*/  RP; int /*<<< orphan*/  RN; int /*<<< orphan*/  QP; int /*<<< orphan*/  DQ; int /*<<< orphan*/  DP; int /*<<< orphan*/  Q; int /*<<< orphan*/  P; int /*<<< orphan*/  D; int /*<<< orphan*/  E; int /*<<< orphan*/  N; int /*<<< orphan*/  len; int /*<<< orphan*/  ver; } ;
typedef  TYPE_1__ mbedtls_rsa_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_rsa_free (TYPE_1__*) ; 

int mbedtls_rsa_copy( mbedtls_rsa_context *dst, const mbedtls_rsa_context *src )
{
    int ret;

    dst->ver = src->ver;
    dst->len = src->len;

    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->N, &src->N ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->E, &src->E ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->D, &src->D ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->P, &src->P ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->Q, &src->Q ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->DP, &src->DP ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->DQ, &src->DQ ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->QP, &src->QP ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->RN, &src->RN ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->RP, &src->RP ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->RQ, &src->RQ ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->Vi, &src->Vi ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &dst->Vf, &src->Vf ) );

    dst->padding = src->padding;
    dst->hash_id = src->hash_id;

cleanup:
    if( ret != 0 )
        mbedtls_rsa_free( dst );

    return( ret );
}
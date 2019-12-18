#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_mod_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_set_bit (int /*<<< orphan*/ *,size_t,int) ; 

__attribute__((used)) static int calculate_rinv(mbedtls_mpi *Rinv, const mbedtls_mpi *M, int num_words)
{
    int ret;
    size_t num_bits = num_words * 32;
    mbedtls_mpi RR;
    mbedtls_mpi_init(&RR);
    MBEDTLS_MPI_CHK(mbedtls_mpi_set_bit(&RR, num_bits * 2, 1));
    MBEDTLS_MPI_CHK(mbedtls_mpi_mod_mpi(Rinv, &RR, M));

 cleanup:
    mbedtls_mpi_free(&RR);
    return ret;
}
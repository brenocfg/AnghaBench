#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int s; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_MEM_X_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MEM_Z_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MULT_START_REG ; 
 int /*<<< orphan*/  mbedtls_mpi_grow (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  mem_block_to_mpi (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mpi_to_mem_block (int /*<<< orphan*/ ,TYPE_1__ const*,size_t) ; 
 int /*<<< orphan*/  start_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_op_complete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int modular_multiply_finish(mbedtls_mpi *Z, const mbedtls_mpi *X, const mbedtls_mpi *Y, size_t hw_words, size_t z_words)
{
    int ret = 0;

    /* Load Y to X input memory block, rerun */
    mpi_to_mem_block(RSA_MEM_X_BLOCK_BASE, Y, hw_words);

    start_op(RSA_MULT_START_REG);

    MBEDTLS_MPI_CHK( mbedtls_mpi_grow(Z, z_words) );

    wait_op_complete(RSA_MULT_START_REG);

    mem_block_to_mpi(Z, RSA_MEM_Z_BLOCK_BASE, z_words);

    Z->s = X->s * Y->s;

 cleanup:
    return ret;
}
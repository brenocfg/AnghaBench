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
typedef  size_t uint32_t ;
typedef  scalar_t__ mbedtls_mpi_uint ;
typedef  int /*<<< orphan*/  const mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  DPORT_REG_WRITE (int /*<<< orphan*/ ,size_t) ; 
 size_t MAX (size_t,size_t) ; 
 int MBEDTLS_ERR_MPI_NOT_ACCEPTABLE ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_LENGTH_REG ; 
 int /*<<< orphan*/  RSA_MEM_M_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MEM_RB_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MEM_X_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MEM_Y_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MEM_Z_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MOD_MULT_START_REG ; 
 int /*<<< orphan*/  RSA_M_DASH_REG ; 
 int /*<<< orphan*/  calculate_rinv (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  esp_mpi_acquire_hardware () ; 
 int /*<<< orphan*/  esp_mpi_release_hardware () ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mem_block_to_mpi (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ modular_inverse (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mpi_to_mem_block (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 size_t mpi_words (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  start_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_op_complete (int /*<<< orphan*/ ) ; 

int esp_mpi_mul_mpi_mod(mbedtls_mpi *Z, const mbedtls_mpi *X, const mbedtls_mpi *Y, const mbedtls_mpi *M)
{
    int ret;
    size_t m_words = mpi_words(M);
    mbedtls_mpi Rinv;
    mbedtls_mpi_uint Mprime;

    size_t num_words = MAX(MAX(m_words, mpi_words(X)), mpi_words(Y));

    if (num_words * 32 > 4096) {
        return MBEDTLS_ERR_MPI_NOT_ACCEPTABLE;
    }

    /* Calculate and load the first stage montgomery multiplication */
    mbedtls_mpi_init(&Rinv);
    MBEDTLS_MPI_CHK(calculate_rinv(&Rinv, M, m_words));
    Mprime = modular_inverse(M);

    esp_mpi_acquire_hardware();

    DPORT_REG_WRITE(RSA_LENGTH_REG, (num_words - 1));
    DPORT_REG_WRITE(RSA_M_DASH_REG, (uint32_t)Mprime);

    /* Load M, X, Rinv, Mprime (Mprime is mod 2^32) */
    mpi_to_mem_block(RSA_MEM_M_BLOCK_BASE, M, num_words);
    mpi_to_mem_block(RSA_MEM_X_BLOCK_BASE, X, num_words);
    mpi_to_mem_block(RSA_MEM_Y_BLOCK_BASE, Y, num_words);
    mpi_to_mem_block(RSA_MEM_RB_BLOCK_BASE, &Rinv, num_words);

    /* Execute first stage montgomery multiplication */
    start_op(RSA_MOD_MULT_START_REG);

    wait_op_complete(RSA_MOD_MULT_START_REG);

    mem_block_to_mpi(Z, RSA_MEM_Z_BLOCK_BASE, m_words);

    esp_mpi_release_hardware();

 cleanup:
    mbedtls_mpi_free(&Rinv);
    return ret;
}
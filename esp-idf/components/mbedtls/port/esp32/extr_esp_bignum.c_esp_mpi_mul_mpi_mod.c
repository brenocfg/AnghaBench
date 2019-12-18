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
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  RSA_MEM_M_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MEM_RB_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MEM_X_BLOCK_BASE ; 
 int /*<<< orphan*/  RSA_MULT_MODE_REG ; 
 int /*<<< orphan*/  RSA_MULT_START_REG ; 
 int /*<<< orphan*/  RSA_M_DASH_REG ; 
 size_t bits_to_words (size_t) ; 
 int /*<<< orphan*/  calculate_rinv (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  esp_mpi_acquire_hardware () ; 
 int /*<<< orphan*/  esp_mpi_release_hardware () ; 
 size_t hardware_words (size_t) ; 
 size_t mbedtls_mpi_bitlen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/  const*) ; 
 scalar_t__ modular_inverse (int /*<<< orphan*/  const*) ; 
 int modular_multiply_finish (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,size_t) ; 
 int /*<<< orphan*/  mpi_to_mem_block (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  start_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_op_complete (int /*<<< orphan*/ ) ; 

int esp_mpi_mul_mpi_mod(mbedtls_mpi *Z, const mbedtls_mpi *X, const mbedtls_mpi *Y, const mbedtls_mpi *M)
{
    int ret;
    size_t x_bits = mbedtls_mpi_bitlen(X);
    size_t y_bits = mbedtls_mpi_bitlen(Y);
    size_t m_bits = mbedtls_mpi_bitlen(M);
    size_t z_bits = MIN(m_bits, x_bits + y_bits);
    size_t x_words = bits_to_words(x_bits);
    size_t y_words = bits_to_words(y_bits);
    size_t m_words = bits_to_words(m_bits);
    size_t z_words = bits_to_words(z_bits);
    size_t hw_words = hardware_words(MAX(x_words, MAX(y_words, m_words))); /* longest operand */
    mbedtls_mpi Rinv;
    mbedtls_mpi_uint Mprime;

    /* Calculate and load the first stage montgomery multiplication */
    mbedtls_mpi_init(&Rinv);
    MBEDTLS_MPI_CHK(calculate_rinv(&Rinv, M, hw_words));
    Mprime = modular_inverse(M);

    esp_mpi_acquire_hardware();

    /* Load M, X, Rinv, Mprime (Mprime is mod 2^32) */
    mpi_to_mem_block(RSA_MEM_M_BLOCK_BASE, M, hw_words);
    mpi_to_mem_block(RSA_MEM_X_BLOCK_BASE, X, hw_words);
    mpi_to_mem_block(RSA_MEM_RB_BLOCK_BASE, &Rinv, hw_words);
    DPORT_REG_WRITE(RSA_M_DASH_REG, (uint32_t)Mprime);

    /* "mode" register loaded with number of 512-bit blocks, minus 1 */
    DPORT_REG_WRITE(RSA_MULT_MODE_REG, (hw_words / 16) - 1);

    /* Execute first stage montgomery multiplication */
    start_op(RSA_MULT_START_REG);

    wait_op_complete(RSA_MULT_START_REG);

    /* execute second stage */
    ret = modular_multiply_finish(Z, X, Y, hw_words, z_words);

    esp_mpi_release_hardware();

 cleanup:
    mbedtls_mpi_free(&Rinv);
    return ret;
}
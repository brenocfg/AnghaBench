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
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int mbedtls_mpi_bitlen (int /*<<< orphan*/  const*) ; 

int crypto_bignum_bits(const struct crypto_bignum *a)
{
    return mbedtls_mpi_bitlen((const mbedtls_mpi *) a);
}
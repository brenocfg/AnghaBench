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
 int esp_mpi_mul_mpi_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int mbedtls_mpi_mod_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mbedtls_mpi_mul_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int crypto_bignum_mulmod(const struct crypto_bignum *a,
                         const struct crypto_bignum *b,
                         const struct crypto_bignum *c,
                         struct crypto_bignum *d)
{
    int res;
#if ALLOW_EVEN_MOD // Must enable this macro if c is even.
    mbedtls_mpi temp;
    mbedtls_mpi_init(&temp);

    res = mbedtls_mpi_mul_mpi(&temp, (const mbedtls_mpi *) a, (const mbedtls_mpi *) b);
    if (res) {
        return -1;
    }

    res = mbedtls_mpi_mod_mpi((mbedtls_mpi *) d, &temp, (mbedtls_mpi *) c);

    mbedtls_mpi_free(&temp);
#else
    // Works with odd modulus only, but it is faster with HW acceleration
    res = esp_mpi_mul_mpi_mod((mbedtls_mpi *) d, (mbedtls_mpi *) a, (mbedtls_mpi *) b, (mbedtls_mpi *) c);
#endif
    return res ? -1 : 0;
}
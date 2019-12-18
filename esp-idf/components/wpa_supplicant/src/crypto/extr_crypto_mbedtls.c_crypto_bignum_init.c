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
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_zalloc (int) ; 

struct crypto_bignum *crypto_bignum_init(void)
{
    mbedtls_mpi *bn = os_zalloc(sizeof(mbedtls_mpi));
    if (bn == NULL) {
        return NULL;
    }

    mbedtls_mpi_init(bn);

    return (struct crypto_bignum *)bn;
}
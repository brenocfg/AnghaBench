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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int mbedtls_mpi_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_write_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int crypto_bignum_to_bin(const struct crypto_bignum *a,
                         u8 *buf, size_t buflen, size_t padlen)
{
    int num_bytes, offset;

    if (padlen > buflen) {
        return -1;
    }

    num_bytes = mbedtls_mpi_size((mbedtls_mpi *) a);

    if ((size_t) num_bytes > buflen) {
        return -1;
    }
    if (padlen > (size_t) num_bytes) {
        offset = padlen - num_bytes;
    } else {
        offset = 0;
    }

    os_memset(buf, 0, offset);
    mbedtls_mpi_write_binary((mbedtls_mpi *) a, buf + offset, mbedtls_mpi_size((mbedtls_mpi *)a) );

    return num_bytes + offset;
}
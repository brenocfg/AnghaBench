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
typedef  int /*<<< orphan*/  mbedtls_mpi_uint ;

/* Variables and functions */

__attribute__((used)) static void mbedtls_mpi_zeroize( mbedtls_mpi_uint *v, size_t n ) {
    volatile mbedtls_mpi_uint *p = v; while( n-- ) *p++ = 0;
}
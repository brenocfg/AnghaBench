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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void mbedtls_mpi_swap( mbedtls_mpi *X, mbedtls_mpi *Y )
{
    mbedtls_mpi T;

    memcpy( &T,  X, sizeof( mbedtls_mpi ) );
    memcpy(  X,  Y, sizeof( mbedtls_mpi ) );
    memcpy(  Y, &T, sizeof( mbedtls_mpi ) );
}
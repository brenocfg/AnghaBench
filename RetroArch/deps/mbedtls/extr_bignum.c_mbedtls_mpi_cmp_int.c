#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi_uint ;
typedef  int /*<<< orphan*/  mbedtls_mpi_sint ;
struct TYPE_5__ {int s; int n; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int mbedtls_mpi_cmp_mpi (TYPE_1__ const*,TYPE_1__*) ; 

int mbedtls_mpi_cmp_int( const mbedtls_mpi *X, mbedtls_mpi_sint z )
{
    mbedtls_mpi Y;
    mbedtls_mpi_uint p[1];

    *p  = ( z < 0 ) ? -z : z;
    Y.s = ( z < 0 ) ? -1 : 1;
    Y.n = 1;
    Y.p = p;

    return( mbedtls_mpi_cmp_mpi( X, &Y ) );
}
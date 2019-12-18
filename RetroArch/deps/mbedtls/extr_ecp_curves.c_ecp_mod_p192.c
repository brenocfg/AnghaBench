#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi_uint ;
struct TYPE_4__ {int n; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (int) ; 
 int /*<<< orphan*/  LAST ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT ; 
 int WIDTH ; 
 int /*<<< orphan*/  mbedtls_mpi_grow (TYPE_1__*,int) ; 

__attribute__((used)) static int ecp_mod_p192( mbedtls_mpi *N )
{
    int ret;
    mbedtls_mpi_uint c = 0;
    mbedtls_mpi_uint *p, *end;

    /* Make sure we have enough blocks so that A(5) is legal */
    MBEDTLS_MPI_CHK( mbedtls_mpi_grow( N, 6 * WIDTH ) );

    p = N->p;
    end = p + N->n;

    ADD( 3 ); ADD( 5 );             NEXT; /* A0 += A3 + A5 */
    ADD( 3 ); ADD( 4 ); ADD( 5 );   NEXT; /* A1 += A3 + A4 + A5 */
    ADD( 4 ); ADD( 5 );             LAST; /* A2 += A4 + A5 */

cleanup:
    return( ret );
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n; scalar_t__* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 size_t biL ; 
 size_t mbedtls_clz (scalar_t__) ; 

size_t mbedtls_mpi_bitlen( const mbedtls_mpi *X )
{
    size_t i, j;

    if( X->n == 0 )
        return( 0 );

    for( i = X->n - 1; i > 0; i-- )
        if( X->p[i] != 0 )
            break;

    j = biL - mbedtls_clz( X->p[i] );

    return( ( i * biL ) + j );
}
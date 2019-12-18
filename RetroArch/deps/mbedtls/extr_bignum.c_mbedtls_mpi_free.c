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
struct TYPE_3__ {int s; int /*<<< orphan*/ * p; scalar_t__ n; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_zeroize (int /*<<< orphan*/ *,scalar_t__) ; 

void mbedtls_mpi_free( mbedtls_mpi *X )
{
    if( X == NULL )
        return;

    if( X->p != NULL )
    {
        mbedtls_mpi_zeroize( X->p, X->n );
        mbedtls_free( X->p );
    }

    X->s = 1;
    X->n = 0;
    X->p = NULL;
}
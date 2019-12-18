#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ mpi_cmp_ui (TYPE_1__*,int) ; 
 scalar_t__ mpi_copy (TYPE_1__**,TYPE_1__* const) ; 
 scalar_t__ mpi_fdiv_r (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mpi_free (TYPE_1__*) ; 
 scalar_t__ mpi_set (TYPE_1__*,TYPE_1__*) ; 

int
mpi_gcd( MPI g, const MPI xa, const MPI xb )
{
    MPI a = NULL, b = NULL;

    if (mpi_copy(&a, xa) < 0)
	    goto nomem;

    if (mpi_copy(&b, xb) < 0)
	    goto nomem;

    /* TAOCP Vol II, 4.5.2, Algorithm A */
    a->sign = 0;
    b->sign = 0;
    while( mpi_cmp_ui( b, 0 ) ) {
	    if (mpi_fdiv_r( g, a, b ) < 0) /* g used as temorary variable */
		    goto nomem;
	    if (mpi_set(a,b) < 0)
		    goto nomem;
	    if (mpi_set(b,g) < 0)
		    goto nomem;
    }
    if (mpi_set(g, a) < 0)
	    goto nomem;

    mpi_free(a);
    mpi_free(b);
    return !mpi_cmp_ui( g, 1);

 nomem:
    mpi_free(a);
    mpi_free(b);
    return -ENOMEM;
}
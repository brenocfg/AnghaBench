#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int sign; scalar_t__ nlimbs; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ mpi_add (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ mpi_copy (TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/  mpi_free (TYPE_1__*) ; 
 scalar_t__ mpi_sub_ui (TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ mpi_tdiv_qr (TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 

int
mpi_fdiv_qr( MPI quot, MPI rem, MPI dividend, MPI divisor )
{
    int divisor_sign = divisor->sign;
    MPI temp_divisor = NULL;

    if( quot == divisor || rem == divisor ) {
	if (mpi_copy( &temp_divisor, divisor ) < 0)
		return -ENOMEM;
	divisor = temp_divisor;
    }

    if (mpi_tdiv_qr( quot, rem, dividend, divisor ) < 0)
	    goto nomem;

    if( (divisor_sign ^ dividend->sign) && rem->nlimbs ) {
	    if (mpi_sub_ui( quot, quot, 1 ) < 0)
		    goto nomem;
	    if (mpi_add( rem, rem, divisor) < 0)
		    goto nomem;
    }

    if( temp_divisor )
	mpi_free(temp_divisor);

    return 0;

 nomem:
    mpi_free(temp_divisor);
    return -ENOMEM;
}
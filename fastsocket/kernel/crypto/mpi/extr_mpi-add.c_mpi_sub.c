#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 int mpi_add (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ mpi_copy (TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/  mpi_free (TYPE_1__*) ; 

int
mpi_sub(MPI w, MPI u, MPI v)
{
	int rc;

    if( w == v ) {
	    MPI vv;
	if (mpi_copy(&vv, v) < 0)
		return -ENOMEM;
	vv->sign = !vv->sign;
	rc = mpi_add( w, u, vv );
	mpi_free(vv);
    }
    else {
	/* fixme: this is not thread-save (we temp. modify v) */
	v->sign = !v->sign;
	rc = mpi_add( w, u, v );
	v->sign = !v->sign;
    }
    return rc;
}
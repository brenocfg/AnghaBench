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
typedef  int mpi_size_t ;
typedef  unsigned long* mpi_ptr_t ;
typedef  void* mpi_limb_t ;
struct TYPE_5__ {int nlimbs; int sign; int alloced; unsigned long* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ mpi_resize (TYPE_1__*,int) ; 
 void* mpihelp_add_1 (unsigned long*,unsigned long*,int,unsigned long) ; 
 int /*<<< orphan*/  mpihelp_sub_1 (unsigned long*,unsigned long*,int,unsigned long) ; 

int
mpi_add_ui(MPI w, const MPI u, unsigned long v )
{
    mpi_ptr_t wp, up;
    mpi_size_t usize, wsize;
    int usign, wsign;

    usize = u->nlimbs;
    usign = u->sign;
    wsign = 0;

    /* If not space for W (and possible carry), increase space.  */
    wsize = usize + 1;
    if( w->alloced < wsize )
	    if (mpi_resize(w, wsize) < 0)
		    return -ENOMEM;

    /* These must be after realloc (U may be the same as W).  */
    up = u->d;
    wp = w->d;

    if( !usize ) {  /* simple */
	wp[0] = v;
	wsize = v? 1:0;
    }
    else if( !usign ) {  /* mpi is not negative */
	mpi_limb_t cy;
	cy = mpihelp_add_1(wp, up, usize, v);
	wp[usize] = cy;
	wsize = usize + cy;
    }
    else {  /* The signs are different.  Need exact comparison to determine
	     * which operand to subtract from which.  */
	if( usize == 1 && up[0] < v ) {
	    wp[0] = v - up[0];
	    wsize = 1;
	}
	else {
	    mpihelp_sub_1(wp, up, usize, v);
	    /* Size can decrease with at most one limb. */
	    wsize = usize - (wp[usize-1]==0);
	    wsign = 1;
	}
    }

    w->nlimbs = wsize;
    w->sign   = wsign;
    return 0;
}
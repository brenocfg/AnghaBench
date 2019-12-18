#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mpi_size_t ;
typedef  scalar_t__ mpi_ptr_t ;
typedef  scalar_t__ mpi_limb_t ;
struct TYPE_7__ {scalar_t__ nlimbs; int sign; scalar_t__ d; size_t alloced; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPN_COPY (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ mpi_alloc_limb_space (scalar_t__) ; 
 int /*<<< orphan*/  mpi_assign_limb_space (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mpi_free_limb_space (scalar_t__) ; 
 scalar_t__ mpi_resize (TYPE_1__*,scalar_t__) ; 
 scalar_t__ mpihelp_mul (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*) ; 

int
mpi_mul( MPI w, MPI u, MPI v)
{
	int rc = -ENOMEM;
	mpi_size_t usize, vsize, wsize;
	mpi_ptr_t up, vp, wp;
	mpi_limb_t cy;
	int usign, vsign, sign_product;
	int assign_wp=0;
	mpi_ptr_t tmp_limb=NULL;


	if( u->nlimbs < v->nlimbs ) { /* Swap U and V. */
		usize = v->nlimbs;
		usign = v->sign;
		up    = v->d;
		vsize = u->nlimbs;
		vsign = u->sign;
		vp    = u->d;
	}
	else {
		usize = u->nlimbs;
		usign = u->sign;
		up    = u->d;
		vsize = v->nlimbs;
		vsign = v->sign;
		vp    = v->d;
	}
	sign_product = usign ^ vsign;
	wp = w->d;

	/* Ensure W has space enough to store the result.  */
	wsize = usize + vsize;
	if( w->alloced < (size_t)wsize ) {
		if( wp == up || wp == vp ) {
			wp = mpi_alloc_limb_space(wsize);
			if (!wp) goto nomem;
			assign_wp = 1;
		}
		else {
			if (mpi_resize(w, wsize ) < 0) goto nomem;
			wp = w->d;
		}
	}
	else { /* Make U and V not overlap with W.	*/
		if( wp == up ) {
			/* W and U are identical.  Allocate temporary space for U.	*/
			up = tmp_limb = mpi_alloc_limb_space( usize);
			if (!up) goto nomem;
			/* Is V identical too?  Keep it identical with U.  */
			if( wp == vp )
				vp = up;
			/* Copy to the temporary space.  */
			MPN_COPY( up, wp, usize );
		}
		else if( wp == vp ) {
			/* W and V are identical.  Allocate temporary space for V.	*/
			vp = tmp_limb = mpi_alloc_limb_space( vsize);
			if (!vp) goto nomem;
			/* Copy to the temporary space.  */
			MPN_COPY( vp, wp, vsize );
		}
	}

	if( !vsize )
		wsize = 0;
	else {
		if (mpihelp_mul( wp, up, usize, vp, vsize, &cy) < 0)
			goto nomem;
		wsize -= cy? 0:1;
	}

	if( assign_wp )
		mpi_assign_limb_space( w, wp, wsize );

	w->nlimbs = wsize;
	w->sign = sign_product;
	rc = 0;
 nomem:
	if( tmp_limb )
		mpi_free_limb_space( tmp_limb );
	return rc;
}
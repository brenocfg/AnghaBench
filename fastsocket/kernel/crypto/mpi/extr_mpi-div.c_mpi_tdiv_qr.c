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
typedef  int mpi_size_t ;
typedef  scalar_t__* mpi_ptr_t ;
typedef  scalar_t__ mpi_limb_t ;
typedef  int /*<<< orphan*/  marker ;
struct TYPE_7__ {int nlimbs; int sign; scalar_t__* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPN_COPY (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  MPN_NORMALIZE (scalar_t__*,int) ; 
 int /*<<< orphan*/  count_leading_zeros (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__**,int /*<<< orphan*/ ,int) ; 
 scalar_t__* mpi_alloc_limb_space (int) ; 
 int /*<<< orphan*/  mpi_free_limb_space (scalar_t__*) ; 
 scalar_t__ mpi_resize (TYPE_1__*,int) ; 
 scalar_t__ mpihelp_divmod_1 (scalar_t__*,scalar_t__*,int,scalar_t__) ; 
 scalar_t__ mpihelp_divrem (scalar_t__*,int /*<<< orphan*/ ,scalar_t__*,int,scalar_t__*,int) ; 
 scalar_t__ mpihelp_lshift (scalar_t__*,scalar_t__*,int,unsigned int) ; 
 scalar_t__ mpihelp_mod_1 (scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  mpihelp_rshift (scalar_t__*,scalar_t__*,int,unsigned int) ; 

int
mpi_tdiv_qr( MPI quot, MPI rem, MPI num, MPI den)
{
	int rc = -ENOMEM;
	mpi_ptr_t np, dp;
	mpi_ptr_t qp, rp;
	mpi_size_t nsize = num->nlimbs;
	mpi_size_t dsize = den->nlimbs;
	mpi_size_t qsize, rsize;
	mpi_size_t sign_remainder = num->sign;
	mpi_size_t sign_quotient = num->sign ^ den->sign;
	unsigned normalization_steps;
	mpi_limb_t q_limb;
	mpi_ptr_t marker[5];
	int markidx=0;

	memset(marker,0,sizeof(marker));

	/* Ensure space is enough for quotient and remainder.
	 * We need space for an extra limb in the remainder, because it's
	 * up-shifted (normalized) below.  */
	rsize = nsize + 1;
	if (mpi_resize( rem, rsize) < 0) goto nomem;

	qsize = rsize - dsize;	  /* qsize cannot be bigger than this.	*/
	if( qsize <= 0 ) {
		if( num != rem ) {
			rem->nlimbs = num->nlimbs;
			rem->sign = num->sign;
			MPN_COPY(rem->d, num->d, nsize);
		}
		if( quot ) {
			/* This needs to follow the assignment to rem, in case the
			 * numerator and quotient are the same.  */
			quot->nlimbs = 0;
			quot->sign = 0;
		}
		return 0;
	}

	if( quot )
		if (mpi_resize( quot, qsize) < 0) goto nomem;

	/* Read pointers here, when reallocation is finished.  */
	np = num->d;
	dp = den->d;
	rp = rem->d;

	/* Optimize division by a single-limb divisor.  */
	if( dsize == 1 ) {
		mpi_limb_t rlimb;
		if( quot ) {
			qp = quot->d;
			rlimb = mpihelp_divmod_1( qp, np, nsize, dp[0] );
			qsize -= qp[qsize - 1] == 0;
			quot->nlimbs = qsize;
			quot->sign = sign_quotient;
		}
		else
			rlimb = mpihelp_mod_1( np, nsize, dp[0] );
		rp[0] = rlimb;
		rsize = rlimb != 0?1:0;
		rem->nlimbs = rsize;
		rem->sign = sign_remainder;
		return 0;
	}


	if( quot ) {
		qp = quot->d;
		/* Make sure QP and NP point to different objects.  Otherwise the
		 * numerator would be gradually overwritten by the quotient limbs.  */
		if(qp == np) { /* Copy NP object to temporary space.  */
			np = marker[markidx++] = mpi_alloc_limb_space(nsize);
			MPN_COPY(np, qp, nsize);
		}
	}
	else /* Put quotient at top of remainder. */
		qp = rp + dsize;

	count_leading_zeros( normalization_steps, dp[dsize - 1] );

	/* Normalize the denominator, i.e. make its most significant bit set by
	 * shifting it NORMALIZATION_STEPS bits to the left.  Also shift the
	 * numerator the same number of steps (to keep the quotient the same!).
	 */
	if( normalization_steps ) {
		mpi_ptr_t tp;
		mpi_limb_t nlimb;

		/* Shift up the denominator setting the most significant bit of
		 * the most significant word.  Use temporary storage not to clobber
		 * the original contents of the denominator.  */
		tp = marker[markidx++] = mpi_alloc_limb_space(dsize);
		if (!tp) goto nomem;
		mpihelp_lshift( tp, dp, dsize, normalization_steps );
		dp = tp;

		/* Shift up the numerator, possibly introducing a new most
		 * significant word.  Move the shifted numerator in the remainder
		 * meanwhile.  */
		nlimb = mpihelp_lshift(rp, np, nsize, normalization_steps);
		if( nlimb ) {
			rp[nsize] = nlimb;
			rsize = nsize + 1;
		}
		else
			rsize = nsize;
	}
	else {
		/* The denominator is already normalized, as required.	Copy it to
		 * temporary space if it overlaps with the quotient or remainder.  */
		if( dp == rp || (quot && (dp == qp))) {
			mpi_ptr_t tp;

			tp = marker[markidx++] = mpi_alloc_limb_space(dsize);
			if (!tp) goto nomem;
			MPN_COPY( tp, dp, dsize );
			dp = tp;
		}

		/* Move the numerator to the remainder.  */
		if( rp != np )
			MPN_COPY(rp, np, nsize);

		rsize = nsize;
	}

	q_limb = mpihelp_divrem( qp, 0, rp, rsize, dp, dsize );

	if( quot ) {
		qsize = rsize - dsize;
		if(q_limb) {
			qp[qsize] = q_limb;
			qsize += 1;
		}

		quot->nlimbs = qsize;
		quot->sign = sign_quotient;
	}

	rsize = dsize;
	MPN_NORMALIZE (rp, rsize);

	if( normalization_steps && rsize ) {
		mpihelp_rshift(rp, rp, rsize, normalization_steps);
		rsize -= rp[rsize - 1] == 0?1:0;
	}

	rem->nlimbs = rsize;
	rem->sign	= sign_remainder;

	rc = 0;
 nomem:
	while( markidx )
		mpi_free_limb_space(marker[--markidx]);
	return rc;
}
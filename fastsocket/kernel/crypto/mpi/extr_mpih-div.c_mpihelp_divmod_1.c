#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int mpi_size_t ;
typedef  int* mpi_ptr_t ;
typedef  int mpi_limb_t ;

/* Variables and functions */
 int BITS_PER_MPI_LIMB ; 
 scalar_t__ UDIV_NEEDS_NORMALIZATION ; 
 int /*<<< orphan*/  UDIV_QRNND_PREINV (int,int,int,int,int,int) ; 
 int UDIV_TIME ; 
 int UMUL_TIME ; 
 int /*<<< orphan*/  count_leading_zeros (int,int) ; 
 int /*<<< orphan*/  udiv_qrnnd (int,int,int,int,int) ; 

mpi_limb_t
mpihelp_divmod_1( mpi_ptr_t quot_ptr,
		  mpi_ptr_t dividend_ptr, mpi_size_t dividend_size,
		  mpi_limb_t divisor_limb)
{
    mpi_size_t i;
    mpi_limb_t n1, n0, r;
    int dummy;

    if( !dividend_size )
	return 0;

    /* If multiplication is much faster than division, and the
     * dividend is large, pre-invert the divisor, and use
     * only multiplications in the inner loop.
     *
     * This test should be read:
     * Does it ever help to use udiv_qrnnd_preinv?
     * && Does what we save compensate for the inversion overhead?
     */
    if( UDIV_TIME > (2 * UMUL_TIME + 6)
	&& (UDIV_TIME - (2 * UMUL_TIME + 6)) * dividend_size > UDIV_TIME ) {
	int normalization_steps;

	count_leading_zeros( normalization_steps, divisor_limb );
	if( normalization_steps ) {
	    mpi_limb_t divisor_limb_inverted;

	    divisor_limb <<= normalization_steps;

	    /* Compute (2**2N - 2**N * DIVISOR_LIMB) / DIVISOR_LIMB.  The
	     * result is a (N+1)-bit approximation to 1/DIVISOR_LIMB, with the
	     * most significant bit (with weight 2**N) implicit.
	     */
	    /* Special case for DIVISOR_LIMB == 100...000.  */
	    if( !(divisor_limb << 1) )
		divisor_limb_inverted = ~(mpi_limb_t)0;
	    else
		udiv_qrnnd(divisor_limb_inverted, dummy,
			   -divisor_limb, 0, divisor_limb);

	    n1 = dividend_ptr[dividend_size - 1];
	    r = n1 >> (BITS_PER_MPI_LIMB - normalization_steps);

	    /* Possible optimization:
	     * if (r == 0
	     * && divisor_limb > ((n1 << normalization_steps)
	     *		       | (dividend_ptr[dividend_size - 2] >> ...)))
	     * ...one division less...
	     */
	    for( i = dividend_size - 2; i >= 0; i--) {
		n0 = dividend_ptr[i];
		UDIV_QRNND_PREINV( quot_ptr[i + 1], r, r,
				   ((n1 << normalization_steps)
			 | (n0 >> (BITS_PER_MPI_LIMB - normalization_steps))),
			      divisor_limb, divisor_limb_inverted);
		n1 = n0;
	    }
	    UDIV_QRNND_PREINV( quot_ptr[0], r, r,
			       n1 << normalization_steps,
			       divisor_limb, divisor_limb_inverted);
	    return r >> normalization_steps;
	}
	else {
	    mpi_limb_t divisor_limb_inverted;

	    /* Compute (2**2N - 2**N * DIVISOR_LIMB) / DIVISOR_LIMB.  The
	     * result is a (N+1)-bit approximation to 1/DIVISOR_LIMB, with the
	     * most significant bit (with weight 2**N) implicit.
	     */
	    /* Special case for DIVISOR_LIMB == 100...000.  */
	    if( !(divisor_limb << 1) )
		divisor_limb_inverted = ~(mpi_limb_t) 0;
	    else
		udiv_qrnnd(divisor_limb_inverted, dummy,
			   -divisor_limb, 0, divisor_limb);

	    i = dividend_size - 1;
	    r = dividend_ptr[i];

	    if( r >= divisor_limb )
		r = 0;
	    else
		quot_ptr[i--] = 0;

	    for( ; i >= 0; i-- ) {
		n0 = dividend_ptr[i];
		UDIV_QRNND_PREINV( quot_ptr[i], r, r,
				   n0, divisor_limb, divisor_limb_inverted);
	    }
	    return r;
	}
    }
    else {
	if(UDIV_NEEDS_NORMALIZATION) {
	    int normalization_steps;

	    count_leading_zeros (normalization_steps, divisor_limb);
	    if( normalization_steps ) {
		divisor_limb <<= normalization_steps;

		n1 = dividend_ptr[dividend_size - 1];
		r = n1 >> (BITS_PER_MPI_LIMB - normalization_steps);

		/* Possible optimization:
		 * if (r == 0
		 * && divisor_limb > ((n1 << normalization_steps)
		 *		   | (dividend_ptr[dividend_size - 2] >> ...)))
		 * ...one division less...
		 */
		for( i = dividend_size - 2; i >= 0; i--) {
		    n0 = dividend_ptr[i];
		    udiv_qrnnd (quot_ptr[i + 1], r, r,
			     ((n1 << normalization_steps)
			 | (n0 >> (BITS_PER_MPI_LIMB - normalization_steps))),
				divisor_limb);
		    n1 = n0;
		}
		udiv_qrnnd (quot_ptr[0], r, r,
			    n1 << normalization_steps,
			    divisor_limb);
		return r >> normalization_steps;
	    }
	}
	/* No normalization needed, either because udiv_qrnnd doesn't require
	 * it, or because DIVISOR_LIMB is already normalized.  */
	i = dividend_size - 1;
	r = dividend_ptr[i];

	if(r >= divisor_limb)
	    r = 0;
	else
	    quot_ptr[i--] = 0;

	for(; i >= 0; i--) {
	    n0 = dividend_ptr[i];
	    udiv_qrnnd( quot_ptr[i], r, r, n0, divisor_limb );
	}
	return r;
    }
}
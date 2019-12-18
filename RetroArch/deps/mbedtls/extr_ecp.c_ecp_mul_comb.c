#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mbedtls_mpi ;
struct TYPE_20__ {int /*<<< orphan*/  X; int /*<<< orphan*/  Y; } ;
typedef  TYPE_2__ mbedtls_ecp_point ;
struct TYPE_19__ {int /*<<< orphan*/  X; int /*<<< orphan*/  Y; } ;
struct TYPE_21__ {int nbits; unsigned char T_size; int /*<<< orphan*/  const N; TYPE_2__* T; TYPE_1__ G; } ;
typedef  TYPE_3__ mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  COMB_MAX_D ; 
 unsigned char MBEDTLS_ECP_WINDOW_SIZE ; 
 int MBEDTLS_ERR_ECP_ALLOC_FAILED ; 
 int MBEDTLS_ERR_ECP_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecp_comb_fixed (unsigned char*,size_t,unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecp_mul_comb_core (TYPE_3__*,TYPE_2__*,TYPE_2__*,unsigned char,unsigned char*,size_t,int (*) (void*,unsigned char*,size_t),void*) ; 
 int /*<<< orphan*/  ecp_normalize_jac (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ecp_precompute_comb (TYPE_3__*,TYPE_2__*,TYPE_2__ const*,unsigned char,size_t) ; 
 int /*<<< orphan*/  ecp_safe_invert_jac (TYPE_3__*,TYPE_2__*,int) ; 
 scalar_t__ mbedtls_calloc (unsigned char,int) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_free (TYPE_2__*) ; 
 scalar_t__ mbedtls_mpi_cmp_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (int /*<<< orphan*/ *) ; 
 int mbedtls_mpi_get_bit (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_safe_cond_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_mpi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ecp_mul_comb( mbedtls_ecp_group *grp, mbedtls_ecp_point *R,
                         const mbedtls_mpi *m, const mbedtls_ecp_point *P,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng )
{
    int ret;
    unsigned char w, m_is_odd, p_eq_g, pre_len, i;
    size_t d;
    unsigned char k[COMB_MAX_D + 1];
    mbedtls_ecp_point *T;
    mbedtls_mpi M, mm;

    mbedtls_mpi_init( &M );
    mbedtls_mpi_init( &mm );

    /* we need N to be odd to trnaform m in an odd number, check now */
    if( mbedtls_mpi_get_bit( &grp->N, 0 ) != 1 )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    /*
     * Minimize the number of multiplications, that is minimize
     * 10 * d * w + 18 * 2^(w-1) + 11 * d + 7 * w, with d = ceil( nbits / w )
     * (see costs of the various parts, with 1S = 1M)
     */
    w = grp->nbits >= 384 ? 5 : 4;

    /*
     * If P == G, pre-compute a bit more, since this may be re-used later.
     * Just adding one avoids upping the cost of the first mul too much,
     * and the memory cost too.
     */
#if MBEDTLS_ECP_FIXED_POINT_OPTIM == 1
    p_eq_g = ( mbedtls_mpi_cmp_mpi( &P->Y, &grp->G.Y ) == 0 &&
               mbedtls_mpi_cmp_mpi( &P->X, &grp->G.X ) == 0 );
    if( p_eq_g )
        w++;
#else
    p_eq_g = 0;
#endif

    /*
     * Make sure w is within bounds.
     * (The last test is useful only for very small curves in the test suite.)
     */
    if( w > MBEDTLS_ECP_WINDOW_SIZE )
        w = MBEDTLS_ECP_WINDOW_SIZE;
    if( w >= grp->nbits )
        w = 2;

    /* Other sizes that depend on w */
    pre_len = 1U << ( w - 1 );
    d = ( grp->nbits + w - 1 ) / w;

    /*
     * Prepare precomputed points: if P == G we want to
     * use grp->T if already initialized, or initialize it.
     */
    T = p_eq_g ? grp->T : NULL;

    if( T == NULL )
    {
        T = (mbedtls_ecp_point*)mbedtls_calloc( pre_len, sizeof( mbedtls_ecp_point ) );
        if( T == NULL )
        {
            ret = MBEDTLS_ERR_ECP_ALLOC_FAILED;
            goto cleanup;
        }

        MBEDTLS_MPI_CHK( ecp_precompute_comb( grp, T, P, w, d ) );

        if( p_eq_g )
        {
            grp->T = T;
            grp->T_size = pre_len;
        }
    }

    /*
     * Make sure M is odd (M = m or M = N - m, since N is odd)
     * using the fact that m * P = - (N - m) * P
     */
    m_is_odd = ( mbedtls_mpi_get_bit( m, 0 ) == 1 );
    MBEDTLS_MPI_CHK( mbedtls_mpi_copy( &M, m ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( &mm, &grp->N, m ) );
    MBEDTLS_MPI_CHK( mbedtls_mpi_safe_cond_assign( &M, &mm, ! m_is_odd ) );

    /*
     * Go for comb multiplication, R = M * P
     */
    ecp_comb_fixed( k, d, w, &M );
    MBEDTLS_MPI_CHK( ecp_mul_comb_core( grp, R, T, pre_len, k, d, f_rng, p_rng ) );

    /*
     * Now get m * P from M * P and normalize it
     */
    MBEDTLS_MPI_CHK( ecp_safe_invert_jac( grp, R, ! m_is_odd ) );
    MBEDTLS_MPI_CHK( ecp_normalize_jac( grp, R ) );

cleanup:

    if( T != NULL && ! p_eq_g )
    {
        for( i = 0; i < pre_len; i++ )
            mbedtls_ecp_point_free( &T[i] );
        mbedtls_free( T );
    }

    mbedtls_mpi_free( &M );
    mbedtls_mpi_free( &mm );

    if( ret != 0 )
        mbedtls_ecp_point_free( R );

    return( ret );
}
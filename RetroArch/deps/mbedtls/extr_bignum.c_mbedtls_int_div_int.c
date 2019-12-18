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
typedef  int mbedtls_t_udbl ;
typedef  int mbedtls_mpi_uint ;
typedef  int mbedtls_mpi_sint ;

/* Variables and functions */
 int biH ; 
 int biL ; 
 size_t mbedtls_clz (int) ; 

__attribute__((used)) static mbedtls_mpi_uint mbedtls_int_div_int( mbedtls_mpi_uint u1,
            mbedtls_mpi_uint u0, mbedtls_mpi_uint d, mbedtls_mpi_uint *r )
{
#if defined(MBEDTLS_HAVE_UDBL)
    mbedtls_t_udbl dividend, quotient;
#else
    const mbedtls_mpi_uint radix = (mbedtls_mpi_uint) 1 << biH;
    const mbedtls_mpi_uint uint_halfword_mask = ( (mbedtls_mpi_uint) 1 << biH ) - 1;
    mbedtls_mpi_uint d0, d1, q0, q1, rAX, r0, quotient;
    mbedtls_mpi_uint u0_msw, u0_lsw;
    size_t s;
#endif

    /*
     * Check for overflow
     */
    if( 0 == d || u1 >= d )
    {
        if (r != NULL) *r = ~0;

        return ( ~0 );
    }

#if defined(MBEDTLS_HAVE_UDBL)
    dividend  = (mbedtls_t_udbl) u1 << biL;
    dividend |= (mbedtls_t_udbl) u0;
    quotient = dividend / d;
    if( quotient > ( (mbedtls_t_udbl) 1 << biL ) - 1 )
        quotient = ( (mbedtls_t_udbl) 1 << biL ) - 1;

    if( r != NULL )
        *r = (mbedtls_mpi_uint)( dividend - (quotient * d ) );

    return (mbedtls_mpi_uint) quotient;
#else

    /*
     * Algorithm D, Section 4.3.1 - The Art of Computer Programming
     *   Vol. 2 - Seminumerical Algorithms, Knuth
     */

    /*
     * Normalize the divisor, d, and dividend, u0, u1
     */
    s = mbedtls_clz( d );
    d = d << s;

    u1 = u1 << s;
    u1 |= ( u0 >> ( biL - s ) ) & ( -(mbedtls_mpi_sint)s >> ( biL - 1 ) );
    u0 =  u0 << s;

    d1 = d >> biH;
    d0 = d & uint_halfword_mask;

    u0_msw = u0 >> biH;
    u0_lsw = u0 & uint_halfword_mask;

    /*
     * Find the first quotient and remainder
     */
    q1 = u1 / d1;
    r0 = u1 - d1 * q1;

    while( q1 >= radix || ( q1 * d0 > radix * r0 + u0_msw ) )
    {
        q1 -= 1;
        r0 += d1;

        if ( r0 >= radix ) break;
    }

    rAX = ( u1 * radix ) + ( u0_msw - q1 * d );
    q0 = rAX / d1;
    r0 = rAX - q0 * d1;

    while( q0 >= radix || ( q0 * d0 > radix * r0 + u0_lsw ) )
    {
        q0 -= 1;
        r0 += d1;

        if ( r0 >= radix ) break;
    }

    if (r != NULL)
        *r = ( rAX * radix + u0_lsw - q0 * d ) >> s;

    quotient = q1 * radix + q0;

    return quotient;
#endif
}
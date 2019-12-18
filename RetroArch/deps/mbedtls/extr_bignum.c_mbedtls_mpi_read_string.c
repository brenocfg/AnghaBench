#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mbedtls_mpi_uint ;
struct TYPE_13__ {int s; size_t* p; } ;
typedef  TYPE_1__ mbedtls_mpi ;

/* Variables and functions */
 size_t BITS_TO_LIMBS (size_t) ; 
 int MBEDTLS_ERR_MPI_BAD_INPUT_DATA ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 size_t MPI_SIZE_T_MAX ; 
 int ciL ; 
 int /*<<< orphan*/  mbedtls_mpi_add_int (TYPE_1__*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  mbedtls_mpi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_grow (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  mbedtls_mpi_init (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_mpi_lset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_mpi_mul_int (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mbedtls_mpi_sub_int (TYPE_1__*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  mpi_get_digit (size_t*,int,char const) ; 
 size_t strlen (char const*) ; 

int mbedtls_mpi_read_string( mbedtls_mpi *X, int radix, const char *s )
{
    int ret;
    size_t i, j, slen, n;
    mbedtls_mpi_uint d;
    mbedtls_mpi T;

    if( radix < 2 || radix > 16 )
        return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

    mbedtls_mpi_init( &T );

    slen = strlen( s );

    if( radix == 16 )
    {
        if( slen > MPI_SIZE_T_MAX >> 2 )
            return( MBEDTLS_ERR_MPI_BAD_INPUT_DATA );

        n = BITS_TO_LIMBS( slen << 2 );

        MBEDTLS_MPI_CHK( mbedtls_mpi_grow( X, n ) );
        MBEDTLS_MPI_CHK( mbedtls_mpi_lset( X, 0 ) );

        for( i = slen, j = 0; i > 0; i--, j++ )
        {
            if( i == 1 && s[i - 1] == '-' )
            {
                X->s = -1;
                break;
            }

            MBEDTLS_MPI_CHK( mpi_get_digit( &d, radix, s[i - 1] ) );
            X->p[j / ( 2 * ciL )] |= d << ( ( j % ( 2 * ciL ) ) << 2 );
        }
    }
    else
    {
        MBEDTLS_MPI_CHK( mbedtls_mpi_lset( X, 0 ) );

        for( i = 0; i < slen; i++ )
        {
            if( i == 0 && s[i] == '-' )
            {
                X->s = -1;
                continue;
            }

            MBEDTLS_MPI_CHK( mpi_get_digit( &d, radix, s[i] ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_mul_int( &T, X, radix ) );

            if( X->s == 1 )
            {
                MBEDTLS_MPI_CHK( mbedtls_mpi_add_int( X, &T, d ) );
            }
            else
            {
                MBEDTLS_MPI_CHK( mbedtls_mpi_sub_int( X, &T, d ) );
            }
        }
    }

cleanup:

    mbedtls_mpi_free( &T );

    return( ret );
}
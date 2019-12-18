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
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  mbedtls_mpi_uint ;
typedef  int /*<<< orphan*/  mbedtls_mpi ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL ; 
 int MBEDTLS_ERR_MPI_FILE_IO_ERROR ; 
 int MBEDTLS_MPI_RW_BUFFER_SIZE ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int mbedtls_mpi_read_string (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpi_get_digit (int /*<<< orphan*/ *,int,char) ; 
 size_t strlen (char*) ; 

int mbedtls_mpi_read_file( mbedtls_mpi *X, int radix, FILE *fin )
{
    mbedtls_mpi_uint d;
    size_t slen;
    char *p;
    /*
     * Buffer should have space for (short) label and decimal formatted MPI,
     * newline characters and '\0'
     */
    char s[ MBEDTLS_MPI_RW_BUFFER_SIZE ];

    memset( s, 0, sizeof( s ) );
    if( fgets( s, sizeof( s ) - 1, fin ) == NULL )
        return( MBEDTLS_ERR_MPI_FILE_IO_ERROR );

    slen = strlen( s );
    if( slen == sizeof( s ) - 2 )
        return( MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL );

    if( slen > 0 && s[slen - 1] == '\n' ) { slen--; s[slen] = '\0'; }
    if( slen > 0 && s[slen - 1] == '\r' ) { slen--; s[slen] = '\0'; }

    p = s + slen;
    while( p-- > s )
        if( mpi_get_digit( &d, radix, *p ) != 0 )
            break;

    return( mbedtls_mpi_read_string( X, radix, p + 1 ) );
}
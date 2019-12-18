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
typedef  int /*<<< orphan*/  mbedtls_mpi ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MBEDTLS_ERR_MPI_FILE_IO_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_MPI_CHK (int /*<<< orphan*/ ) ; 
 int MBEDTLS_MPI_RW_BUFFER_SIZE ; 
 size_t fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_mpi_write_string (int /*<<< orphan*/  const*,int,char*,int,size_t*) ; 
 int /*<<< orphan*/  mbedtls_printf (char*,char const*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char const*) ; 

int mbedtls_mpi_write_file( const char *p, const mbedtls_mpi *X, int radix, FILE *fout )
{
    int ret;
    size_t n, slen, plen;
    /*
     * Buffer should have space for (short) label and decimal formatted MPI,
     * newline characters and '\0'
     */
    char s[ MBEDTLS_MPI_RW_BUFFER_SIZE ];

    memset( s, 0, sizeof( s ) );

    MBEDTLS_MPI_CHK( mbedtls_mpi_write_string( X, radix, s, sizeof( s ) - 2, &n ) );

    if( p == NULL ) p = "";

    plen = strlen( p );
    slen = strlen( s );
    s[slen++] = '\r';
    s[slen++] = '\n';

    if( fout != NULL )
    {
        if( fwrite( p, 1, plen, fout ) != plen ||
            fwrite( s, 1, slen, fout ) != slen )
            return( MBEDTLS_ERR_MPI_FILE_IO_ERROR );
    }
    else
        mbedtls_printf( "%s%s", p, s );

cleanup:

    return( ret );
}
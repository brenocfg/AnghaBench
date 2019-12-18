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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MBEDTLS_ERR_DHM_ALLOC_FAILED ; 
 int MBEDTLS_ERR_DHM_FILE_IO_ERROR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_calloc (int,size_t) ; 
 int /*<<< orphan*/  mbedtls_free (unsigned char*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static int load_file( const char *path, unsigned char **buf, size_t *n )
{
    FILE *f;
    long size;

    if( ( f = fopen( path, "rb" ) ) == NULL )
        return( MBEDTLS_ERR_DHM_FILE_IO_ERROR );

    fseek( f, 0, SEEK_END );
    if( ( size = ftell( f ) ) == -1 )
    {
        fclose( f );
        return( MBEDTLS_ERR_DHM_FILE_IO_ERROR );
    }
    fseek( f, 0, SEEK_SET );

    *n = (size_t) size;

    if( *n + 1 == 0 ||
        ( *buf = (unsigned char*)mbedtls_calloc( 1, *n + 1 ) ) == NULL )
    {
        fclose( f );
        return( MBEDTLS_ERR_DHM_ALLOC_FAILED );
    }

    if( fread( *buf, 1, *n, f ) != *n )
    {
        fclose( f );
        mbedtls_free( *buf );
        return( MBEDTLS_ERR_DHM_FILE_IO_ERROR );
    }

    fclose( f );

    (*buf)[*n] = '\0';

    if( strstr( (const char *) *buf, "-----BEGIN " ) != NULL )
        ++*n;

    return( 0 );
}
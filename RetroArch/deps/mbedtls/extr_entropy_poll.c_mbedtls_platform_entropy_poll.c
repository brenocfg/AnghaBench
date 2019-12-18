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
 int MBEDTLS_ERR_ENTROPY_SOURCE_FAILED ; 
 scalar_t__ check_version_3_17_plus () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 int getrandom_wrapper (unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int has_getrandom ; 

int mbedtls_platform_entropy_poll( void *data,
                           unsigned char *output, size_t len, size_t *olen )
{
    FILE *file;
    size_t read_len;
    ((void) data);

#if defined(HAVE_GETRANDOM)
    if( has_getrandom == -1 )
        has_getrandom = ( check_version_3_17_plus() == 0 );

    if( has_getrandom )
    {
        int ret;

        if( ( ret = getrandom_wrapper( output, len, 0 ) ) < 0 )
            return( MBEDTLS_ERR_ENTROPY_SOURCE_FAILED );

        *olen = ret;
        return( 0 );
    }
#endif /* HAVE_GETRANDOM */

    *olen = 0;

    file = fopen( "/dev/urandom", "rb" );
    if( file == NULL )
        return( MBEDTLS_ERR_ENTROPY_SOURCE_FAILED );

    read_len = fread( output, 1, len, file );
    if( read_len != len )
    {
        fclose( file );
        return( MBEDTLS_ERR_ENTROPY_SOURCE_FAILED );
    }

    fclose( file );
    *olen = len;

    return( 0 );
}
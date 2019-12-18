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
typedef  int /*<<< orphan*/  mbedtls_hmac_drbg_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MBEDTLS_ERR_HMAC_DRBG_FILE_IO_ERROR ; 
 int MBEDTLS_ERR_HMAC_DRBG_INPUT_TOO_BIG ; 
 int MBEDTLS_HMAC_DRBG_MAX_INPUT ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_hmac_drbg_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int mbedtls_hmac_drbg_write_seed_file (int /*<<< orphan*/ *,char const*) ; 

int mbedtls_hmac_drbg_update_seed_file( mbedtls_hmac_drbg_context *ctx, const char *path )
{
    FILE *f;
    size_t n;
    unsigned char buf[ MBEDTLS_HMAC_DRBG_MAX_INPUT ];

    if( ( f = fopen( path, "rb" ) ) == NULL )
        return( MBEDTLS_ERR_HMAC_DRBG_FILE_IO_ERROR );

    fseek( f, 0, SEEK_END );
    n = (size_t) ftell( f );
    fseek( f, 0, SEEK_SET );

    if( n > MBEDTLS_HMAC_DRBG_MAX_INPUT )
    {
        fclose( f );
        return( MBEDTLS_ERR_HMAC_DRBG_INPUT_TOO_BIG );
    }

    if( fread( buf, 1, n, f ) != n )
    {
        fclose( f );
        return( MBEDTLS_ERR_HMAC_DRBG_FILE_IO_ERROR );
    }

    fclose( f );

    mbedtls_hmac_drbg_update( ctx, buf, n );

    return( mbedtls_hmac_drbg_write_seed_file( ctx, path ) );
}
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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MBEDTLS_ERR_HMAC_DRBG_FILE_IO_ERROR ; 
 int MBEDTLS_HMAC_DRBG_MAX_INPUT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fwrite (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int mbedtls_hmac_drbg_random (int /*<<< orphan*/ *,unsigned char*,int) ; 

int mbedtls_hmac_drbg_write_seed_file( mbedtls_hmac_drbg_context *ctx, const char *path )
{
    int ret;
    FILE *f;
    unsigned char buf[ MBEDTLS_HMAC_DRBG_MAX_INPUT ];

    if( ( f = fopen( path, "wb" ) ) == NULL )
        return( MBEDTLS_ERR_HMAC_DRBG_FILE_IO_ERROR );

    if( ( ret = mbedtls_hmac_drbg_random( ctx, buf, sizeof( buf ) ) ) != 0 )
        goto exit;

    if( fwrite( buf, 1, sizeof( buf ), f ) != sizeof( buf ) )
    {
        ret = MBEDTLS_ERR_HMAC_DRBG_FILE_IO_ERROR;
        goto exit;
    }

    ret = 0;

exit:
    fclose( f );
    return( ret );
}
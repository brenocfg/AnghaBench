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
typedef  int /*<<< orphan*/  output_buf ;
typedef  int /*<<< orphan*/  mbedtls_pk_context ;

/* Variables and functions */
 int MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE ; 
 scalar_t__ MBEDTLS_PK_ECKEY ; 
 scalar_t__ MBEDTLS_PK_RSA ; 
 char* PEM_BEGIN_PRIVATE_KEY_EC ; 
 char* PEM_BEGIN_PRIVATE_KEY_RSA ; 
 char* PEM_END_PRIVATE_KEY_EC ; 
 char* PEM_END_PRIVATE_KEY_RSA ; 
 int PRV_DER_MAX_BYTES ; 
 int mbedtls_pem_write_buffer (char const*,char const*,unsigned char*,int,unsigned char*,size_t,size_t*) ; 
 scalar_t__ mbedtls_pk_get_type (int /*<<< orphan*/ *) ; 
 int mbedtls_pk_write_key_der (int /*<<< orphan*/ *,unsigned char*,int) ; 

int mbedtls_pk_write_key_pem( mbedtls_pk_context *key, unsigned char *buf, size_t size )
{
    int ret;
    unsigned char output_buf[PRV_DER_MAX_BYTES];
    const char *begin, *end;
    size_t olen = 0;

    if( ( ret = mbedtls_pk_write_key_der( key, output_buf, sizeof(output_buf) ) ) < 0 )
        return( ret );

#if defined(MBEDTLS_RSA_C)
    if( mbedtls_pk_get_type( key ) == MBEDTLS_PK_RSA )
    {
        begin = PEM_BEGIN_PRIVATE_KEY_RSA;
        end = PEM_END_PRIVATE_KEY_RSA;
    }
    else
#endif
#if defined(MBEDTLS_ECP_C)
    if( mbedtls_pk_get_type( key ) == MBEDTLS_PK_ECKEY )
    {
        begin = PEM_BEGIN_PRIVATE_KEY_EC;
        end = PEM_END_PRIVATE_KEY_EC;
    }
    else
#endif
        return( MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE );

    if( ( ret = mbedtls_pem_write_buffer( begin, end,
                                  output_buf + sizeof(output_buf) - ret,
                                  ret, buf, size, &olen ) ) != 0 )
    {
        return( ret );
    }

    return( 0 );
}
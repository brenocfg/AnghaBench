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

/* Variables and functions */
#define  MBEDTLS_MD_MD5 133 
#define  MBEDTLS_MD_SHA1 132 
#define  MBEDTLS_MD_SHA224 131 
#define  MBEDTLS_MD_SHA256 130 
#define  MBEDTLS_MD_SHA384 129 
#define  MBEDTLS_MD_SHA512 128 
 unsigned char MBEDTLS_SSL_HASH_MD5 ; 
 unsigned char MBEDTLS_SSL_HASH_NONE ; 
 unsigned char MBEDTLS_SSL_HASH_SHA1 ; 
 unsigned char MBEDTLS_SSL_HASH_SHA224 ; 
 unsigned char MBEDTLS_SSL_HASH_SHA256 ; 
 unsigned char MBEDTLS_SSL_HASH_SHA384 ; 
 unsigned char MBEDTLS_SSL_HASH_SHA512 ; 

unsigned char mbedtls_ssl_hash_from_md_alg( int md )
{
    switch( md )
    {
#if defined(MBEDTLS_MD5_C)
        case MBEDTLS_MD_MD5:
            return( MBEDTLS_SSL_HASH_MD5 );
#endif
#if defined(MBEDTLS_SHA1_C)
        case MBEDTLS_MD_SHA1:
            return( MBEDTLS_SSL_HASH_SHA1 );
#endif
#if defined(MBEDTLS_SHA256_C)
        case MBEDTLS_MD_SHA224:
            return( MBEDTLS_SSL_HASH_SHA224 );
        case MBEDTLS_MD_SHA256:
            return( MBEDTLS_SSL_HASH_SHA256 );
#endif
#if defined(MBEDTLS_SHA512_C)
        case MBEDTLS_MD_SHA384:
            return( MBEDTLS_SSL_HASH_SHA384 );
        case MBEDTLS_MD_SHA512:
            return( MBEDTLS_SSL_HASH_SHA512 );
#endif
        default:
            return( MBEDTLS_SSL_HASH_NONE );
    }
}
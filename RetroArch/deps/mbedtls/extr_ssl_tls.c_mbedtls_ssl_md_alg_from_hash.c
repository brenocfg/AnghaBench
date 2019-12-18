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
typedef  int /*<<< orphan*/  mbedtls_md_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MD_MD5 ; 
 int /*<<< orphan*/  MBEDTLS_MD_NONE ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA1 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA224 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA256 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA384 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA512 ; 
#define  MBEDTLS_SSL_HASH_MD5 133 
#define  MBEDTLS_SSL_HASH_SHA1 132 
#define  MBEDTLS_SSL_HASH_SHA224 131 
#define  MBEDTLS_SSL_HASH_SHA256 130 
#define  MBEDTLS_SSL_HASH_SHA384 129 
#define  MBEDTLS_SSL_HASH_SHA512 128 

mbedtls_md_type_t mbedtls_ssl_md_alg_from_hash( unsigned char hash )
{
    switch( hash )
    {
#if defined(MBEDTLS_MD5_C)
        case MBEDTLS_SSL_HASH_MD5:
            return( MBEDTLS_MD_MD5 );
#endif
#if defined(MBEDTLS_SHA1_C)
        case MBEDTLS_SSL_HASH_SHA1:
            return( MBEDTLS_MD_SHA1 );
#endif
#if defined(MBEDTLS_SHA256_C)
        case MBEDTLS_SSL_HASH_SHA224:
            return( MBEDTLS_MD_SHA224 );
        case MBEDTLS_SSL_HASH_SHA256:
            return( MBEDTLS_MD_SHA256 );
#endif
#if defined(MBEDTLS_SHA512_C)
        case MBEDTLS_SSL_HASH_SHA384:
            return( MBEDTLS_MD_SHA384 );
        case MBEDTLS_SSL_HASH_SHA512:
            return( MBEDTLS_MD_SHA512 );
#endif
        default:
            return( MBEDTLS_MD_NONE );
    }
}
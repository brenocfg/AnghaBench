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
typedef  int mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;

/* Variables and functions */
#define  MBEDTLS_MD_MD2 136 
#define  MBEDTLS_MD_MD4 135 
#define  MBEDTLS_MD_MD5 134 
#define  MBEDTLS_MD_RIPEMD160 133 
#define  MBEDTLS_MD_SHA1 132 
#define  MBEDTLS_MD_SHA224 131 
#define  MBEDTLS_MD_SHA256 130 
#define  MBEDTLS_MD_SHA384 129 
#define  MBEDTLS_MD_SHA512 128 
 int /*<<< orphan*/  const mbedtls_md2_info ; 
 int /*<<< orphan*/  const mbedtls_md4_info ; 
 int /*<<< orphan*/  const mbedtls_md5_info ; 
 int /*<<< orphan*/  const mbedtls_ripemd160_info ; 
 int /*<<< orphan*/  const mbedtls_sha1_info ; 
 int /*<<< orphan*/  const mbedtls_sha224_info ; 
 int /*<<< orphan*/  const mbedtls_sha256_info ; 
 int /*<<< orphan*/  const mbedtls_sha384_info ; 
 int /*<<< orphan*/  const mbedtls_sha512_info ; 

const mbedtls_md_info_t *mbedtls_md_info_from_type( mbedtls_md_type_t md_type )
{
    switch( md_type )
    {
#if defined(MBEDTLS_MD2_C)
        case MBEDTLS_MD_MD2:
            return( &mbedtls_md2_info );
#endif
#if defined(MBEDTLS_MD4_C)
        case MBEDTLS_MD_MD4:
            return( &mbedtls_md4_info );
#endif
#if defined(MBEDTLS_MD5_C)
        case MBEDTLS_MD_MD5:
            return( &mbedtls_md5_info );
#endif
#if defined(MBEDTLS_RIPEMD160_C)
        case MBEDTLS_MD_RIPEMD160:
            return( &mbedtls_ripemd160_info );
#endif
#if defined(MBEDTLS_SHA1_C)
        case MBEDTLS_MD_SHA1:
            return( &mbedtls_sha1_info );
#endif
#if defined(MBEDTLS_SHA256_C)
        case MBEDTLS_MD_SHA224:
            return( &mbedtls_sha224_info );
        case MBEDTLS_MD_SHA256:
            return( &mbedtls_sha256_info );
#endif
#if defined(MBEDTLS_SHA512_C)
        case MBEDTLS_MD_SHA384:
            return( &mbedtls_sha384_info );
        case MBEDTLS_MD_SHA512:
            return( &mbedtls_sha512_info );
#endif
        default:
            return( NULL );
    }
}
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
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_MD_MD2 ; 
 int /*<<< orphan*/  MBEDTLS_MD_MD4 ; 
 int /*<<< orphan*/  MBEDTLS_MD_MD5 ; 
 int /*<<< orphan*/  MBEDTLS_MD_RIPEMD160 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA1 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA224 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA256 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA384 ; 
 int /*<<< orphan*/  MBEDTLS_MD_SHA512 ; 
 int /*<<< orphan*/  const* mbedtls_md_info_from_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

const mbedtls_md_info_t *mbedtls_md_info_from_string( const char *md_name )
{
    if( NULL == md_name )
        return( NULL );

    /* Get the appropriate digest information */
#if defined(MBEDTLS_MD2_C)
    if( !strcmp( "MD2", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_MD2 );
#endif
#if defined(MBEDTLS_MD4_C)
    if( !strcmp( "MD4", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_MD4 );
#endif
#if defined(MBEDTLS_MD5_C)
    if( !strcmp( "MD5", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_MD5 );
#endif
#if defined(MBEDTLS_RIPEMD160_C)
    if( !strcmp( "RIPEMD160", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_RIPEMD160 );
#endif
#if defined(MBEDTLS_SHA1_C)
    if( !strcmp( "SHA1", md_name ) || !strcmp( "SHA", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_SHA1 );
#endif
#if defined(MBEDTLS_SHA256_C)
    if( !strcmp( "SHA224", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_SHA224 );
    if( !strcmp( "SHA256", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_SHA256 );
#endif
#if defined(MBEDTLS_SHA512_C)
    if( !strcmp( "SHA384", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_SHA384 );
    if( !strcmp( "SHA512", md_name ) )
        return mbedtls_md_info_from_type( MBEDTLS_MD_SHA512 );
#endif
    return( NULL );
}
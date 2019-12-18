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
typedef  int /*<<< orphan*/  mbedtls_pk_context ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_PK_ECDSA ; 
 int /*<<< orphan*/  MBEDTLS_PK_RSA ; 
 unsigned char MBEDTLS_SSL_SIG_ANON ; 
 unsigned char MBEDTLS_SSL_SIG_ECDSA ; 
 unsigned char MBEDTLS_SSL_SIG_RSA ; 
 scalar_t__ mbedtls_pk_can_do (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

unsigned char mbedtls_ssl_sig_from_pk( mbedtls_pk_context *pk )
{
#if defined(MBEDTLS_RSA_C)
    if( mbedtls_pk_can_do( pk, MBEDTLS_PK_RSA ) )
        return( MBEDTLS_SSL_SIG_RSA );
#endif
#if defined(MBEDTLS_ECDSA_C)
    if( mbedtls_pk_can_do( pk, MBEDTLS_PK_ECDSA ) )
        return( MBEDTLS_SSL_SIG_ECDSA );
#endif
    return( MBEDTLS_SSL_SIG_ANON );
}
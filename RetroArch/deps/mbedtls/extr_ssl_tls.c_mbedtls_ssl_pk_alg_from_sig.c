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
typedef  int /*<<< orphan*/  mbedtls_pk_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_PK_ECDSA ; 
 int /*<<< orphan*/  MBEDTLS_PK_NONE ; 
 int /*<<< orphan*/  MBEDTLS_PK_RSA ; 
#define  MBEDTLS_SSL_SIG_ECDSA 129 
#define  MBEDTLS_SSL_SIG_RSA 128 

mbedtls_pk_type_t mbedtls_ssl_pk_alg_from_sig( unsigned char sig )
{
    switch( sig )
    {
#if defined(MBEDTLS_RSA_C)
        case MBEDTLS_SSL_SIG_RSA:
            return( MBEDTLS_PK_RSA );
#endif
#if defined(MBEDTLS_ECDSA_C)
        case MBEDTLS_SSL_SIG_ECDSA:
            return( MBEDTLS_PK_ECDSA );
#endif
        default:
            return( MBEDTLS_PK_NONE );
    }
}
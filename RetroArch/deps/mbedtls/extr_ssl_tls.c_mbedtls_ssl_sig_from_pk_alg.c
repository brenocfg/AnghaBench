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
typedef  int mbedtls_pk_type_t ;

/* Variables and functions */
#define  MBEDTLS_PK_ECDSA 130 
#define  MBEDTLS_PK_ECKEY 129 
#define  MBEDTLS_PK_RSA 128 
 unsigned char MBEDTLS_SSL_SIG_ANON ; 
 unsigned char MBEDTLS_SSL_SIG_ECDSA ; 
 unsigned char MBEDTLS_SSL_SIG_RSA ; 

unsigned char mbedtls_ssl_sig_from_pk_alg( mbedtls_pk_type_t type )
{
    switch( type ) {
        case MBEDTLS_PK_RSA:
            return( MBEDTLS_SSL_SIG_RSA );
        case MBEDTLS_PK_ECDSA:
        case MBEDTLS_PK_ECKEY:
            return( MBEDTLS_SSL_SIG_ECDSA );
        default:
            return( MBEDTLS_SSL_SIG_ANON );
    }
}
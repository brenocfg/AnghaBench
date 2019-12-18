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
typedef  int /*<<< orphan*/  mbedtls_pk_info_t ;

/* Variables and functions */
#define  MBEDTLS_PK_ECDSA 131 
#define  MBEDTLS_PK_ECKEY 130 
#define  MBEDTLS_PK_ECKEY_DH 129 
#define  MBEDTLS_PK_RSA 128 
 int /*<<< orphan*/  const mbedtls_ecdsa_info ; 
 int /*<<< orphan*/  const mbedtls_eckey_info ; 
 int /*<<< orphan*/  const mbedtls_eckeydh_info ; 
 int /*<<< orphan*/  const mbedtls_rsa_info ; 

const mbedtls_pk_info_t * mbedtls_pk_info_from_type( mbedtls_pk_type_t pk_type )
{
    switch( pk_type ) {
#if defined(MBEDTLS_RSA_C)
        case MBEDTLS_PK_RSA:
            return( &mbedtls_rsa_info );
#endif
#if defined(MBEDTLS_ECP_C)
        case MBEDTLS_PK_ECKEY:
            return( &mbedtls_eckey_info );
        case MBEDTLS_PK_ECKEY_DH:
            return( &mbedtls_eckeydh_info );
#endif
#if defined(MBEDTLS_ECDSA_C)
        case MBEDTLS_PK_ECDSA:
            return( &mbedtls_ecdsa_info );
#endif
        /* MBEDTLS_PK_RSA_ALT omitted on purpose */
        default:
            return( NULL );
    }
}
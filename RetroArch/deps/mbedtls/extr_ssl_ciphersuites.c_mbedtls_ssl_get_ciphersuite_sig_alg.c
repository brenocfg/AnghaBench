#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int key_exchange; } ;
typedef  TYPE_1__ mbedtls_ssl_ciphersuite_t ;
typedef  int /*<<< orphan*/  mbedtls_pk_type_t ;

/* Variables and functions */
#define  MBEDTLS_KEY_EXCHANGE_DHE_RSA 131 
#define  MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA 130 
#define  MBEDTLS_KEY_EXCHANGE_ECDHE_RSA 129 
#define  MBEDTLS_KEY_EXCHANGE_RSA 128 
 int /*<<< orphan*/  MBEDTLS_PK_ECDSA ; 
 int /*<<< orphan*/  MBEDTLS_PK_NONE ; 
 int /*<<< orphan*/  MBEDTLS_PK_RSA ; 

mbedtls_pk_type_t mbedtls_ssl_get_ciphersuite_sig_alg( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_RSA:
        case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
            return( MBEDTLS_PK_RSA );

        case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
            return( MBEDTLS_PK_ECDSA );

        default:
            return( MBEDTLS_PK_NONE );
    }
}
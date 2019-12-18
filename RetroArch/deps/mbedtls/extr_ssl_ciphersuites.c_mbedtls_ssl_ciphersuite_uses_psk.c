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

/* Variables and functions */
#define  MBEDTLS_KEY_EXCHANGE_DHE_PSK 131 
#define  MBEDTLS_KEY_EXCHANGE_ECDHE_PSK 130 
#define  MBEDTLS_KEY_EXCHANGE_PSK 129 
#define  MBEDTLS_KEY_EXCHANGE_RSA_PSK 128 

int mbedtls_ssl_ciphersuite_uses_psk( const mbedtls_ssl_ciphersuite_t *info )
{
    switch( info->key_exchange )
    {
        case MBEDTLS_KEY_EXCHANGE_PSK:
        case MBEDTLS_KEY_EXCHANGE_RSA_PSK:
        case MBEDTLS_KEY_EXCHANGE_DHE_PSK:
        case MBEDTLS_KEY_EXCHANGE_ECDHE_PSK:
            return( 1 );

        default:
            return( 0 );
    }
}
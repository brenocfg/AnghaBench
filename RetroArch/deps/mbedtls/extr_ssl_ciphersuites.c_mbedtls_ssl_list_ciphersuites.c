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
struct TYPE_3__ {scalar_t__ cipher; } ;
typedef  TYPE_1__ mbedtls_ssl_ciphersuite_t ;

/* Variables and functions */
 int MAX_CIPHERSUITES ; 
 scalar_t__ MBEDTLS_CIPHER_ARC4_128 ; 
 int* ciphersuite_preference ; 
 TYPE_1__* mbedtls_ssl_ciphersuite_from_id (int const) ; 
 int ssl_ciphersuites_supported_init ; 
 int* supported_ciphersuites ; 

const int *mbedtls_ssl_list_ciphersuites( void )
{
    /*
     * On initial call filter out all ciphersuites not supported by current
     * build based on presence in the ciphersuite_definitions.
     */
    if( ssl_ciphersuites_supported_init == 0 )
    {
        const int *p;
        int *q;

        for( p = ciphersuite_preference, q = supported_ciphersuites;
             *p != 0 && q < supported_ciphersuites + MAX_CIPHERSUITES - 1;
             p++ )
        {
#if defined(MBEDTLS_REMOVE_ARC4_CIPHERSUITES)
            const mbedtls_ssl_ciphersuite_t *cs_info;
            if( ( cs_info = mbedtls_ssl_ciphersuite_from_id( *p ) ) != NULL &&
                cs_info->cipher != MBEDTLS_CIPHER_ARC4_128 )
#else
            if( mbedtls_ssl_ciphersuite_from_id( *p ) != NULL )
#endif
                *(q++) = *p;
        }
        *q = 0;

        ssl_ciphersuites_supported_init = 1;
    }

    return( supported_ciphersuites );
}
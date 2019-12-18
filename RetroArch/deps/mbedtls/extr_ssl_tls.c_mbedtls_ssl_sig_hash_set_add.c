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
struct TYPE_3__ {void* ecdsa; void* rsa; } ;
typedef  TYPE_1__ mbedtls_ssl_sig_hash_set_t ;
typedef  int mbedtls_pk_type_t ;
typedef  void* mbedtls_md_type_t ;

/* Variables and functions */
 void* MBEDTLS_MD_NONE ; 
#define  MBEDTLS_PK_ECDSA 129 
#define  MBEDTLS_PK_RSA 128 

void mbedtls_ssl_sig_hash_set_add( mbedtls_ssl_sig_hash_set_t *set,
                                   mbedtls_pk_type_t sig_alg,
                                   mbedtls_md_type_t md_alg )
{
    switch( sig_alg )
    {
        case MBEDTLS_PK_RSA:
            if( set->rsa == MBEDTLS_MD_NONE )
                set->rsa = md_alg;
            break;

        case MBEDTLS_PK_ECDSA:
            if( set->ecdsa == MBEDTLS_MD_NONE )
                set->ecdsa = md_alg;
            break;

        default:
            break;
    }
}
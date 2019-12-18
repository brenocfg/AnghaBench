#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mbedtls_cipher_mode_t ;
struct TYPE_7__ {unsigned int key_bitlen; scalar_t__ const mode; TYPE_1__* base; } ;
typedef  TYPE_2__ mbedtls_cipher_info_t ;
typedef  scalar_t__ mbedtls_cipher_id_t ;
struct TYPE_8__ {TYPE_2__ const* info; } ;
typedef  TYPE_3__ mbedtls_cipher_definition_t ;
struct TYPE_6__ {scalar_t__ const cipher; } ;

/* Variables and functions */
 TYPE_3__* mbedtls_cipher_definitions ; 

const mbedtls_cipher_info_t *mbedtls_cipher_info_from_values( const mbedtls_cipher_id_t cipher_id,
                                              int key_bitlen,
                                              const mbedtls_cipher_mode_t mode )
{
    const mbedtls_cipher_definition_t *def;

    for( def = mbedtls_cipher_definitions; def->info != NULL; def++ )
        if( def->info->base->cipher == cipher_id &&
            def->info->key_bitlen == (unsigned) key_bitlen &&
            def->info->mode == mode )
            return( def->info );

    return( NULL );
}
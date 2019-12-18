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
typedef  scalar_t__ mbedtls_cipher_type_t ;
typedef  int /*<<< orphan*/  mbedtls_cipher_info_t ;
struct TYPE_3__ {scalar_t__ const type; int /*<<< orphan*/  const* info; } ;
typedef  TYPE_1__ mbedtls_cipher_definition_t ;

/* Variables and functions */
 TYPE_1__* mbedtls_cipher_definitions ; 

const mbedtls_cipher_info_t *mbedtls_cipher_info_from_type( const mbedtls_cipher_type_t cipher_type )
{
    const mbedtls_cipher_definition_t *def;

    for( def = mbedtls_cipher_definitions; def->info != NULL; def++ )
        if( def->type == cipher_type )
            return( def->info );

    return( NULL );
}
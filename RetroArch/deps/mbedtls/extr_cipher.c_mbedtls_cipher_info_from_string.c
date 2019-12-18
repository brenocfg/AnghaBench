#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ mbedtls_cipher_info_t ;
struct TYPE_6__ {TYPE_1__ const* info; } ;
typedef  TYPE_2__ mbedtls_cipher_definition_t ;

/* Variables and functions */
 TYPE_2__* mbedtls_cipher_definitions ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

const mbedtls_cipher_info_t *mbedtls_cipher_info_from_string( const char *cipher_name )
{
    const mbedtls_cipher_definition_t *def;

    if( NULL == cipher_name )
        return( NULL );

    for( def = mbedtls_cipher_definitions; def->info != NULL; def++ )
        if( !  strcmp( def->info->name, cipher_name ) )
            return( def->info );

    return( NULL );
}
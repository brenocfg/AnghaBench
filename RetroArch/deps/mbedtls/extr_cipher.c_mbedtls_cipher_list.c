#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_2__ mbedtls_cipher_definition_t ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 TYPE_2__* mbedtls_cipher_definitions ; 
 int const* mbedtls_cipher_supported ; 
 int supported_init ; 

const int *mbedtls_cipher_list( void )
{
    const mbedtls_cipher_definition_t *def;
    int *type;

    if( ! supported_init )
    {
        def = mbedtls_cipher_definitions;
        type = mbedtls_cipher_supported;

        while( def->type != 0 )
            *type++ = (*def++).type;

        *type = 0;

        supported_init = 1;
    }

    return( mbedtls_cipher_supported );
}
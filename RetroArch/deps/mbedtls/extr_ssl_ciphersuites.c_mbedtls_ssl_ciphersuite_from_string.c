#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ mbedtls_ssl_ciphersuite_t ;

/* Variables and functions */
 TYPE_1__* ciphersuite_definitions ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

const mbedtls_ssl_ciphersuite_t *mbedtls_ssl_ciphersuite_from_string(
                                                const char *ciphersuite_name )
{
    const mbedtls_ssl_ciphersuite_t *cur = ciphersuite_definitions;

    if( NULL == ciphersuite_name )
        return( NULL );

    while( cur->id != 0 )
    {
        if( 0 == strcmp( cur->name, ciphersuite_name ) )
            return( cur );

        cur++;
    }

    return( NULL );
}
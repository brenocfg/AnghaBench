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
struct TYPE_3__ {int id; } ;
typedef  TYPE_1__ mbedtls_ssl_ciphersuite_t ;

/* Variables and functions */
 TYPE_1__* mbedtls_ssl_ciphersuite_from_string (char const*) ; 

int mbedtls_ssl_get_ciphersuite_id( const char *ciphersuite_name )
{
    const mbedtls_ssl_ciphersuite_t *cur;

    cur = mbedtls_ssl_ciphersuite_from_string( ciphersuite_name );

    if( cur == NULL )
        return( 0 );

    return( cur->id );
}
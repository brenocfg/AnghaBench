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
struct TYPE_3__ {char const* name; } ;
typedef  TYPE_1__ mbedtls_ssl_ciphersuite_t ;

/* Variables and functions */
 TYPE_1__* mbedtls_ssl_ciphersuite_from_id (int const) ; 

const char *mbedtls_ssl_get_ciphersuite_name( const int ciphersuite_id )
{
    const mbedtls_ssl_ciphersuite_t *cur;

    cur = mbedtls_ssl_ciphersuite_from_id( ciphersuite_id );

    if( cur == NULL )
        return( "unknown" );

    return( cur->name );
}
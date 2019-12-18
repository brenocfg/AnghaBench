#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void mbedtls_des3_context ;

/* Variables and functions */
 scalar_t__ mbedtls_calloc (int,int) ; 
 int /*<<< orphan*/  mbedtls_des3_init (void*) ; 

__attribute__((used)) static void * des3_ctx_alloc( void )
{
    mbedtls_des3_context *des3 = (mbedtls_des3_context*)mbedtls_calloc( 1, sizeof( mbedtls_des3_context ) );

    if( des3 == NULL )
        return( NULL );

    mbedtls_des3_init( des3 );

    return( des3 );
}
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
typedef  void mbedtls_blowfish_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_blowfish_init (void*) ; 
 scalar_t__ mbedtls_calloc (int,int) ; 

__attribute__((used)) static void * blowfish_ctx_alloc( void )
{
    mbedtls_blowfish_context *ctx = (mbedtls_blowfish_context*)mbedtls_calloc( 1, sizeof( mbedtls_blowfish_context ) );

    if( ctx == NULL )
        return( NULL );

    mbedtls_blowfish_init( ctx );

    return( ctx );
}
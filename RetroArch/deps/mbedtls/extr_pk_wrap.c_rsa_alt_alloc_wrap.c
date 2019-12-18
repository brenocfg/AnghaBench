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
typedef  int /*<<< orphan*/  mbedtls_rsa_alt_context ;

/* Variables and functions */
 void* mbedtls_calloc (int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *rsa_alt_alloc_wrap( void )
{
    void *ctx = mbedtls_calloc( 1, sizeof( mbedtls_rsa_alt_context ) );

    if( ctx != NULL )
        memset( ctx, 0, sizeof( mbedtls_rsa_alt_context ) );

    return( ctx );
}
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
 int /*<<< orphan*/  mbedtls_free (void*) ; 
 int /*<<< orphan*/  mbedtls_zeroize (void*,int) ; 

__attribute__((used)) static void rsa_alt_free_wrap( void *ctx )
{
    mbedtls_zeroize( ctx, sizeof( mbedtls_rsa_alt_context ) );
    mbedtls_free( ctx );
}
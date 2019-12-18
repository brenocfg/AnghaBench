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
typedef  int /*<<< orphan*/  mbedtls_des3_context ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_des3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_free (void*) ; 

__attribute__((used)) static void des3_ctx_free( void *ctx )
{
    mbedtls_des3_free( (mbedtls_des3_context *) ctx );
    mbedtls_free( ctx );
}
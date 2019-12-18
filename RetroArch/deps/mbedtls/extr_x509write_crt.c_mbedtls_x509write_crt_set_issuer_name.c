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
struct TYPE_3__ {int /*<<< orphan*/  issuer; } ;
typedef  TYPE_1__ mbedtls_x509write_cert ;

/* Variables and functions */
 int mbedtls_x509_string_to_names (int /*<<< orphan*/ *,char const*) ; 

int mbedtls_x509write_crt_set_issuer_name( mbedtls_x509write_cert *ctx,
                                   const char *issuer_name )
{
    return mbedtls_x509_string_to_names( &ctx->issuer, issuer_name );
}
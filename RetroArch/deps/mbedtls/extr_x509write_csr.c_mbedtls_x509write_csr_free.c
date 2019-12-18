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
struct TYPE_4__ {int /*<<< orphan*/  extensions; int /*<<< orphan*/  subject; } ;
typedef  TYPE_1__ mbedtls_x509write_csr ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_asn1_free_named_data_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_1__*,int) ; 

void mbedtls_x509write_csr_free( mbedtls_x509write_csr *ctx )
{
    mbedtls_asn1_free_named_data_list( &ctx->subject );
    mbedtls_asn1_free_named_data_list( &ctx->extensions );

    mbedtls_zeroize( ctx, sizeof(mbedtls_x509write_csr) );
}
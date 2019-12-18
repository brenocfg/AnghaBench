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
struct TYPE_4__ {int /*<<< orphan*/  version; int /*<<< orphan*/  serial; } ;
typedef  TYPE_1__ mbedtls_x509write_cert ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_X509_CRT_VERSION_3 ; 
 int /*<<< orphan*/  mbedtls_mpi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void mbedtls_x509write_crt_init( mbedtls_x509write_cert *ctx )
{
    memset( ctx, 0, sizeof(mbedtls_x509write_cert) );

    mbedtls_mpi_init( &ctx->serial );
    ctx->version = MBEDTLS_X509_CRT_VERSION_3;
}
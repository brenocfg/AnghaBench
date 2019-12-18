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
struct TYPE_3__ {int /*<<< orphan*/  extensions; } ;
typedef  TYPE_1__ mbedtls_x509write_csr ;

/* Variables and functions */
 int mbedtls_x509_set_extension (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

int mbedtls_x509write_csr_set_extension( mbedtls_x509write_csr *ctx,
                                 const char *oid, size_t oid_len,
                                 const unsigned char *val, size_t val_len )
{
    return mbedtls_x509_set_extension( &ctx->extensions, oid, oid_len,
                               0, val, val_len );
}
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
struct TYPE_4__ {int /*<<< orphan*/  md_ctx_dec; int /*<<< orphan*/  md_ctx_enc; int /*<<< orphan*/  cipher_ctx_dec; int /*<<< orphan*/  cipher_ctx_enc; int /*<<< orphan*/  ctx_inflate; int /*<<< orphan*/  ctx_deflate; } ;
typedef  TYPE_1__ mbedtls_ssl_transform ;

/* Variables and functions */
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_cipher_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_zeroize (TYPE_1__*,int) ; 

void mbedtls_ssl_transform_free( mbedtls_ssl_transform *transform )
{
    if( transform == NULL )
        return;

#if defined(MBEDTLS_ZLIB_SUPPORT)
    deflateEnd( &transform->ctx_deflate );
    inflateEnd( &transform->ctx_inflate );
#endif

    mbedtls_cipher_free( &transform->cipher_ctx_enc );
    mbedtls_cipher_free( &transform->cipher_ctx_dec );

    mbedtls_md_free( &transform->md_ctx_enc );
    mbedtls_md_free( &transform->md_ctx_dec );

    mbedtls_zeroize( transform, sizeof( mbedtls_ssl_transform ) );
}
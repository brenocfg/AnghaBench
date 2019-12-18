#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* handshake; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
struct TYPE_4__ {int /*<<< orphan*/  fin_sha512; int /*<<< orphan*/  fin_sha256; int /*<<< orphan*/  fin_sha1; int /*<<< orphan*/  fin_md5; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_md5_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_sha1_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_sha256_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  mbedtls_sha512_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

__attribute__((used)) static void ssl_update_checksum_start( mbedtls_ssl_context *ssl,
                                       const unsigned char *buf, size_t len )
{
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
     mbedtls_md5_update( &ssl->handshake->fin_md5 , buf, len );
    mbedtls_sha1_update( &ssl->handshake->fin_sha1, buf, len );
#endif
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
#if defined(MBEDTLS_SHA256_C)
    mbedtls_sha256_update( &ssl->handshake->fin_sha256, buf, len );
#endif
#if defined(MBEDTLS_SHA512_C)
    mbedtls_sha512_update( &ssl->handshake->fin_sha512, buf, len );
#endif
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
}
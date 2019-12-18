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
struct TYPE_4__ {int /*<<< orphan*/  sni_authmode; scalar_t__ ecjpake_cache_len; int /*<<< orphan*/ * ecjpake_cache; int /*<<< orphan*/  ecjpake_ctx; int /*<<< orphan*/  ecdh_ctx; int /*<<< orphan*/  dhm_ctx; int /*<<< orphan*/  hash_algs; int /*<<< orphan*/  update_checksum; int /*<<< orphan*/  fin_sha512; int /*<<< orphan*/  fin_sha256; int /*<<< orphan*/  fin_sha1; int /*<<< orphan*/  fin_md5; } ;
typedef  TYPE_1__ mbedtls_ssl_handshake_params ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_SSL_VERIFY_UNSET ; 
 int /*<<< orphan*/  mbedtls_dhm_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecdh_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_ecjpake_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha256_starts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha512_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha512_starts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_ssl_sig_hash_set_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssl_update_checksum_start ; 

__attribute__((used)) static void ssl_handshake_params_init( mbedtls_ssl_handshake_params *handshake )
{
    memset( handshake, 0, sizeof( mbedtls_ssl_handshake_params ) );

#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
     mbedtls_md5_init(   &handshake->fin_md5  );
    mbedtls_sha1_init(   &handshake->fin_sha1 );
     mbedtls_md5_starts( &handshake->fin_md5  );
    mbedtls_sha1_starts( &handshake->fin_sha1 );
#endif
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
#if defined(MBEDTLS_SHA256_C)
    mbedtls_sha256_init(   &handshake->fin_sha256    );
    mbedtls_sha256_starts( &handshake->fin_sha256, 0 );
#endif
#if defined(MBEDTLS_SHA512_C)
    mbedtls_sha512_init(   &handshake->fin_sha512    );
    mbedtls_sha512_starts( &handshake->fin_sha512, 1 );
#endif
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */

    handshake->update_checksum = ssl_update_checksum_start;

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
    mbedtls_ssl_sig_hash_set_init( &handshake->hash_algs );
#endif

#if defined(MBEDTLS_DHM_C)
    mbedtls_dhm_init( &handshake->dhm_ctx );
#endif
#if defined(MBEDTLS_ECDH_C)
    mbedtls_ecdh_init( &handshake->ecdh_ctx );
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    mbedtls_ecjpake_init( &handshake->ecjpake_ctx );
#if defined(MBEDTLS_SSL_CLI_C)
    handshake->ecjpake_cache = NULL;
    handshake->ecjpake_cache_len = 0;
#endif
#endif

#if defined(MBEDTLS_SSL_SERVER_NAME_INDICATION)
    handshake->sni_authmode = MBEDTLS_SSL_VERIFY_UNSET;
#endif
}
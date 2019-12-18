#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ minor_ver; TYPE_2__* handshake; TYPE_1__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
struct TYPE_16__ {scalar_t__ min_minor_ver; scalar_t__ max_minor_ver; int flags; scalar_t__ cipher; scalar_t__ key_exchange; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ mbedtls_ssl_ciphersuite_t ;
typedef  scalar_t__ mbedtls_pk_type_t ;
struct TYPE_14__ {int cli_exts; int /*<<< orphan*/  hash_algs; int /*<<< orphan*/ ** curves; } ;
struct TYPE_13__ {scalar_t__ transport; scalar_t__ arc4_disabled; scalar_t__ psk_identity_len; scalar_t__ psk_len; int /*<<< orphan*/ * psk_identity; int /*<<< orphan*/ * psk; int /*<<< orphan*/ * f_psk; } ;

/* Variables and functions */
 int MBEDTLS_CIPHERSUITE_NODTLS ; 
 scalar_t__ MBEDTLS_CIPHER_ARC4_128 ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECJPAKE ; 
 scalar_t__ MBEDTLS_MD_NONE ; 
 scalar_t__ MBEDTLS_PK_NONE ; 
 scalar_t__ MBEDTLS_SSL_ARC4_DISABLED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_3 ; 
 scalar_t__ MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 int MBEDTLS_TLS_EXT_ECJPAKE_KKPP_OK ; 
 TYPE_4__* mbedtls_ssl_ciphersuite_from_id (int) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_uses_ec (TYPE_4__ const*) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_uses_psk (TYPE_4__ const*) ; 
 scalar_t__ mbedtls_ssl_get_ciphersuite_sig_alg (TYPE_4__ const*) ; 
 scalar_t__ mbedtls_ssl_sig_hash_set_find (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ssl_pick_cert (TYPE_3__*,TYPE_4__ const*) ; 

__attribute__((used)) static int ssl_ciphersuite_match( mbedtls_ssl_context *ssl, int suite_id,
                                  const mbedtls_ssl_ciphersuite_t **ciphersuite_info )
{
    const mbedtls_ssl_ciphersuite_t *suite_info;

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
    mbedtls_pk_type_t sig_type;
#endif

    suite_info = mbedtls_ssl_ciphersuite_from_id( suite_id );
    if( suite_info == NULL )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "trying ciphersuite: %s", suite_info->name ) );

    if( suite_info->min_minor_ver > ssl->minor_ver ||
        suite_info->max_minor_ver < ssl->minor_ver )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: version" ) );
        return( 0 );
    }

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    if( ssl->conf->transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM &&
        ( suite_info->flags & MBEDTLS_CIPHERSUITE_NODTLS ) )
        return( 0 );
#endif

#if defined(MBEDTLS_ARC4_C)
    if( ssl->conf->arc4_disabled == MBEDTLS_SSL_ARC4_DISABLED &&
            suite_info->cipher == MBEDTLS_CIPHER_ARC4_128 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: rc4" ) );
        return( 0 );
    }
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    if( suite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE &&
        ( ssl->handshake->cli_exts & MBEDTLS_TLS_EXT_ECJPAKE_KKPP_OK ) == 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: ecjpake "
                                    "not configured or ext missing" ) );
        return( 0 );
    }
#endif


#if defined(MBEDTLS_ECDH_C) || defined(MBEDTLS_ECDSA_C)
    if( mbedtls_ssl_ciphersuite_uses_ec( suite_info ) &&
        ( ssl->handshake->curves == NULL ||
          ssl->handshake->curves[0] == NULL ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: "
                            "no common elliptic curve" ) );
        return( 0 );
    }
#endif

#if defined(MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
    /* If the ciphersuite requires a pre-shared key and we don't
     * have one, skip it now rather than failing later */
    if( mbedtls_ssl_ciphersuite_uses_psk( suite_info ) &&
        ssl->conf->f_psk == NULL &&
        ( ssl->conf->psk == NULL || ssl->conf->psk_identity == NULL ||
          ssl->conf->psk_identity_len == 0 || ssl->conf->psk_len == 0 ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: no pre-shared key" ) );
        return( 0 );
    }
#endif

#if defined(MBEDTLS_SSL_PROTO_TLS1_2) && \
    defined(MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
    /* If the ciphersuite requires signing, check whether
     * a suitable hash algorithm is present. */
    if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
    {
        sig_type = mbedtls_ssl_get_ciphersuite_sig_alg( suite_info );
        if( sig_type != MBEDTLS_PK_NONE &&
            mbedtls_ssl_sig_hash_set_find( &ssl->handshake->hash_algs, sig_type ) == MBEDTLS_MD_NONE )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: no suitable hash algorithm "
                                        "for signature algorithm %d", sig_type ) );
            return( 0 );
        }
    }

#endif /* MBEDTLS_SSL_PROTO_TLS1_2 &&
          MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED */

#if defined(MBEDTLS_X509_CRT_PARSE_C)
    /*
     * Final check: if ciphersuite requires us to have a
     * certificate/key of a particular type:
     * - select the appropriate certificate if we have one, or
     * - try the next ciphersuite if we don't
     * This must be done last since we modify the key_cert list.
     */
    if( ssl_pick_cert( ssl, suite_info ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 3, ( "ciphersuite mismatch: "
                            "no suitable certificate" ) );
        return( 0 );
    }
#endif

    *ciphersuite_info = suite_info;
    return( 0 );
}
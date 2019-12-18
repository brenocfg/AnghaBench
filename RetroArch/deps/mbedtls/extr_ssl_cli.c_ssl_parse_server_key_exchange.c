#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ in_msgtype; scalar_t__* in_msg; int keep_current_message; int in_hslen; scalar_t__ minor_ver; int /*<<< orphan*/  state; TYPE_2__* session_negotiate; TYPE_4__* handshake; TYPE_3__* transform_negotiate; } ;
typedef  TYPE_5__ mbedtls_ssl_context ;
struct TYPE_23__ {scalar_t__ key_exchange; } ;
typedef  TYPE_6__ mbedtls_ssl_ciphersuite_t ;
typedef  int /*<<< orphan*/  mbedtls_sha1_context ;
typedef  scalar_t__ mbedtls_pk_type_t ;
typedef  scalar_t__ mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_md_context_t ;
typedef  int /*<<< orphan*/  mbedtls_md5_context ;
struct TYPE_21__ {unsigned char* randbytes; int /*<<< orphan*/  ecjpake_ctx; } ;
struct TYPE_20__ {TYPE_6__* ciphersuite_info; } ;
struct TYPE_19__ {TYPE_1__* peer_cert; } ;
struct TYPE_18__ {int /*<<< orphan*/  pk; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH ; 
 int MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_DHE_PSK ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_DHE_RSA ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECDHE_PSK ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECDHE_RSA ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECDH_RSA ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECJPAKE ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_PSK ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_RSA ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_RSA_PSK ; 
 scalar_t__ MBEDTLS_MD_NONE ; 
 scalar_t__ MBEDTLS_MD_SHA1 ; 
 scalar_t__ MBEDTLS_PK_ECDSA ; 
 scalar_t__ MBEDTLS_PK_NONE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_DECRYPT_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_BUF (int,char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 scalar_t__ MBEDTLS_SSL_HS_SERVER_KEY_EXCHANGE ; 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_3 ; 
 scalar_t__ MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int mbedtls_ecjpake_read_round_two (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  mbedtls_md5_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md5_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_md_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_md_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_info_from_type (scalar_t__) ; 
 int /*<<< orphan*/  mbedtls_md_init (int /*<<< orphan*/ *) ; 
 int mbedtls_md_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_pk_can_do (int /*<<< orphan*/ *,scalar_t__) ; 
 int mbedtls_pk_verify (int /*<<< orphan*/ *,scalar_t__,unsigned char*,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_sha1_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha1_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_uses_server_signature (TYPE_6__ const*) ; 
 scalar_t__ mbedtls_ssl_get_ciphersuite_sig_pk_alg (TYPE_6__ const*) ; 
 int mbedtls_ssl_hs_hdr_len (TYPE_5__*) ; 
 int mbedtls_ssl_read_record (TYPE_5__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_send_alert_message (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ssl_cli_get_ecdh_params_from_cert (TYPE_5__*) ; 
 scalar_t__ ssl_parse_server_dh_params (TYPE_5__*,unsigned char**,unsigned char*) ; 
 scalar_t__ ssl_parse_server_ecdh_params (TYPE_5__*,unsigned char**,unsigned char*) ; 
 scalar_t__ ssl_parse_server_psk_hint (TYPE_5__*,unsigned char**,unsigned char*) ; 
 scalar_t__ ssl_parse_signature_algorithm (TYPE_5__*,unsigned char**,unsigned char*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int ssl_parse_server_key_exchange( mbedtls_ssl_context *ssl )
{
    int ret;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info =
        ssl->transform_negotiate->ciphersuite_info;
    unsigned char *p, *end;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse server key exchange" ) );

#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip parse server key exchange" ) );
        ssl->state++;
        return( 0 );
    }
    ((void) p);
    ((void) end);
#endif

#if defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED) || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDH_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA )
    {
        if( ( ret = ssl_cli_get_ecdh_params_from_cert( ssl ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "ssl_cli_get_ecdh_params_from_cert", ret );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE );
            return( ret );
        }

        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip parse server key exchange" ) );
        ssl->state++;
        return( 0 );
    }
    ((void) p);
    ((void) end);
#endif /* MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED */

    if( ( ret = mbedtls_ssl_read_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_read_record", ret );
        return( ret );
    }

    if( ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE );
        return( MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE );
    }

    /*
     * ServerKeyExchange may be skipped with PSK and RSA-PSK when the server
     * doesn't use a psk_identity_hint
     */
    if( ssl->in_msg[0] != MBEDTLS_SSL_HS_SERVER_KEY_EXCHANGE )
    {
        if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK ||
            ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK )
        {
            /* Current message is probably either
             * CertificateRequest or ServerHelloDone */
            ssl->keep_current_message = 1;
            goto exit;
        }

        MBEDTLS_SSL_DEBUG_MSG( 1, ( "server key exchange message must "
                                    "not be skipped" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE );

        return( MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE );
    }

    p   = ssl->in_msg + mbedtls_ssl_hs_hdr_len( ssl );
    end = ssl->in_msg + ssl->in_hslen;
    MBEDTLS_SSL_DEBUG_BUF( 3,   "server key exchange", p, end - p );

#if defined(MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK )
    {
        if( ssl_parse_server_psk_hint( ssl, &p, end ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
            return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
        }
    } /* FALLTROUGH */
#endif /* MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED */

#if defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED) ||                       \
    defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK )
        ; /* nothing more to do */
    else
#endif /* MBEDTLS_KEY_EXCHANGE_PSK_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED) ||                       \
    defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK )
    {
        if( ssl_parse_server_dh_params( ssl, &p, end ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
            return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) ||                     \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED) ||                     \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA )
    {
        if( ssl_parse_server_ecdh_params( ssl, &p, end ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
            return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE )
    {
        ret = mbedtls_ecjpake_read_round_two( &ssl->handshake->ecjpake_ctx,
                                              p, end - p );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_read_round_two", ret );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
            return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

#if defined(MBEDTLS_KEY_EXCHANGE__WITH_SERVER_SIGNATURE__ENABLED)
    if( mbedtls_ssl_ciphersuite_uses_server_signature( ciphersuite_info ) )
    {
        size_t sig_len, hashlen;
        unsigned char hash[64];
        mbedtls_md_type_t md_alg = MBEDTLS_MD_NONE;
        mbedtls_pk_type_t pk_alg = MBEDTLS_PK_NONE;
        unsigned char *params = ssl->in_msg + mbedtls_ssl_hs_hdr_len( ssl );
        size_t params_len = p - params;

        /*
         * Handle the digitally-signed structure
         */
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
        {
            if( ssl_parse_signature_algorithm( ssl, &p, end,
                                               &md_alg, &pk_alg ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message" ) );
                mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                                MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
                return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
            }

            if( pk_alg != mbedtls_ssl_get_ciphersuite_sig_pk_alg( ciphersuite_info ) )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message" ) );
                mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                                MBEDTLS_SSL_ALERT_MSG_ILLEGAL_PARAMETER );
                return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
            }
        }
        else
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
        if( ssl->minor_ver < MBEDTLS_SSL_MINOR_VERSION_3 )
        {
            pk_alg = mbedtls_ssl_get_ciphersuite_sig_pk_alg( ciphersuite_info );

            /* Default hash for ECDSA is SHA-1 */
            if( pk_alg == MBEDTLS_PK_ECDSA && md_alg == MBEDTLS_MD_NONE )
                md_alg = MBEDTLS_MD_SHA1;
        }
        else
#endif
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }

        /*
         * Read signature
         */
        sig_len = ( p[0] << 8 ) | p[1];
        p += 2;

        if( end != p + sig_len )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
            return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
        }

        MBEDTLS_SSL_DEBUG_BUF( 3, "signature", p, sig_len );

        /*
         * Compute the hash that has been signed
         */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
        if( md_alg == MBEDTLS_MD_NONE )
        {
            mbedtls_md5_context mbedtls_md5;
            mbedtls_sha1_context mbedtls_sha1;

            mbedtls_md5_init(  &mbedtls_md5  );
            mbedtls_sha1_init( &mbedtls_sha1 );

            hashlen = 36;

            /*
             * digitally-signed struct {
             *     opaque md5_hash[16];
             *     opaque sha_hash[20];
             * };
             *
             * md5_hash
             *     MD5(ClientHello.random + ServerHello.random
             *                            + ServerParams);
             * sha_hash
             *     SHA(ClientHello.random + ServerHello.random
             *                            + ServerParams);
             */
            mbedtls_md5_starts( &mbedtls_md5 );
            mbedtls_md5_update( &mbedtls_md5, ssl->handshake->randbytes, 64 );
            mbedtls_md5_update( &mbedtls_md5, params, params_len );
            mbedtls_md5_finish( &mbedtls_md5, hash );

            mbedtls_sha1_starts( &mbedtls_sha1 );
            mbedtls_sha1_update( &mbedtls_sha1, ssl->handshake->randbytes, 64 );
            mbedtls_sha1_update( &mbedtls_sha1, params, params_len );
            mbedtls_sha1_finish( &mbedtls_sha1, hash + 16 );

            mbedtls_md5_free(  &mbedtls_md5  );
            mbedtls_sha1_free( &mbedtls_sha1 );
        }
        else
#endif /* MBEDTLS_SSL_PROTO_SSL3 || MBEDTLS_SSL_PROTO_TLS1 || \
          MBEDTLS_SSL_PROTO_TLS1_1 */
#if defined(MBEDTLS_SSL_PROTO_TLS1) || defined(MBEDTLS_SSL_PROTO_TLS1_1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( md_alg != MBEDTLS_MD_NONE )
        {
            mbedtls_md_context_t ctx;

            mbedtls_md_init( &ctx );

            /* Info from md_alg will be used instead */
            hashlen = 0;

            /*
             * digitally-signed struct {
             *     opaque client_random[32];
             *     opaque server_random[32];
             *     ServerDHParams params;
             * };
             */
            if( ( ret = mbedtls_md_setup( &ctx,
                                     mbedtls_md_info_from_type( md_alg ), 0 ) ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_md_setup", ret );
                mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                                MBEDTLS_SSL_ALERT_MSG_INTERNAL_ERROR );
                return( ret );
            }

            mbedtls_md_starts( &ctx );
            mbedtls_md_update( &ctx, ssl->handshake->randbytes, 64 );
            mbedtls_md_update( &ctx, params, params_len );
            mbedtls_md_finish( &ctx, hash );
            mbedtls_md_free( &ctx );
        }
        else
#endif /* MBEDTLS_SSL_PROTO_TLS1 || MBEDTLS_SSL_PROTO_TLS1_1 || \
          MBEDTLS_SSL_PROTO_TLS1_2 */
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }

        MBEDTLS_SSL_DEBUG_BUF( 3, "parameters hash", hash, hashlen != 0 ? hashlen :
            (unsigned int) ( mbedtls_md_get_size( mbedtls_md_info_from_type( md_alg ) ) ) );

        if( ssl->session_negotiate->peer_cert == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 2, ( "certificate required" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE );
            return( MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE );
        }

        /*
         * Verify signature
         */
        if( ! mbedtls_pk_can_do( &ssl->session_negotiate->peer_cert->pk, pk_alg ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad server key exchange message" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_HANDSHAKE_FAILURE );
            return( MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH );
        }

        if( ( ret = mbedtls_pk_verify( &ssl->session_negotiate->peer_cert->pk,
                               md_alg, hash, hashlen, p, sig_len ) ) != 0 )
        {
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_DECRYPT_ERROR );
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_pk_verify", ret );
            return( ret );
        }
    }
#endif /* MBEDTLS_KEY_EXCHANGE__WITH_SERVER_SIGNATURE__ENABLED */

exit:
    ssl->state++;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse server key exchange" ) );

    return( 0 );
}
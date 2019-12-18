#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct TYPE_22__ {unsigned char* in_msg; int in_hslen; scalar_t__ in_msgtype; int /*<<< orphan*/  state; TYPE_2__* conf; TYPE_3__* handshake; TYPE_1__* transform_negotiate; } ;
typedef  TYPE_4__ mbedtls_ssl_context ;
struct TYPE_23__ {scalar_t__ key_exchange; } ;
typedef  TYPE_5__ mbedtls_ssl_ciphersuite_t ;
struct TYPE_17__ {int /*<<< orphan*/  Qp; int /*<<< orphan*/  z; } ;
struct TYPE_18__ {int /*<<< orphan*/  K; } ;
struct TYPE_21__ {int /*<<< orphan*/  pmslen; int /*<<< orphan*/  premaster; int /*<<< orphan*/  ecjpake_ctx; TYPE_14__ ecdh_ctx; TYPE_16__ dhm_ctx; } ;
struct TYPE_20__ {int /*<<< orphan*/  p_rng; int /*<<< orphan*/  f_rng; } ;
struct TYPE_19__ {TYPE_5__* ciphersuite_info; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE ; 
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS ; 
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP ; 
 int MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
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
 int /*<<< orphan*/  MBEDTLS_MPI_MAX_SIZE ; 
 int /*<<< orphan*/  MBEDTLS_PREMASTER_SIZE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_ECP (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MPI (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 scalar_t__ MBEDTLS_SSL_HS_CLIENT_KEY_EXCHANGE ; 
 scalar_t__ MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int mbedtls_dhm_calc_secret (TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecdh_calc_secret (TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecdh_read_public (TYPE_14__*,unsigned char*,int) ; 
 int mbedtls_ecjpake_derive_secret (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecjpake_read_round_two (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int mbedtls_ssl_derive_keys (TYPE_4__*) ; 
 int mbedtls_ssl_hs_hdr_len (TYPE_4__*) ; 
 int mbedtls_ssl_psk_derive_premaster (TYPE_4__*,scalar_t__) ; 
 int mbedtls_ssl_read_record (TYPE_4__*) ; 
 int ssl_parse_client_dh_public (TYPE_4__*,unsigned char**,unsigned char*) ; 
 int ssl_parse_client_psk_identity (TYPE_4__*,unsigned char**,unsigned char*) ; 
 int ssl_parse_encrypted_pms (TYPE_4__*,unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int ssl_parse_client_key_exchange( mbedtls_ssl_context *ssl )
{
    int ret;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info;
    unsigned char *p, *end;

    ciphersuite_info = ssl->transform_negotiate->ciphersuite_info;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse client key exchange" ) );

    if( ( ret = mbedtls_ssl_read_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_read_record", ret );
        return( ret );
    }

    p = ssl->in_msg + mbedtls_ssl_hs_hdr_len( ssl );
    end = ssl->in_msg + ssl->in_hslen;

    if( ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    if( ssl->in_msg[0] != MBEDTLS_SSL_HS_CLIENT_KEY_EXCHANGE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_RSA )
    {
        if( ( ret = ssl_parse_client_dh_public( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_dh_public" ), ret );
            return( ret );
        }

        if( p != end )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
        }

        if( ( ret = mbedtls_dhm_calc_secret( &ssl->handshake->dhm_ctx,
                                      ssl->handshake->premaster,
                                      MBEDTLS_PREMASTER_SIZE,
                                     &ssl->handshake->pmslen,
                                      ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_calc_secret", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS );
        }

        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: K ", &ssl->handshake->dhm_ctx.K  );
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED) ||                     \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED) ||                   \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED) ||                      \
    defined(MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDH_RSA ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA )
    {
        if( ( ret = mbedtls_ecdh_read_public( &ssl->handshake->ecdh_ctx,
                                      p, end - p) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_read_public", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP );
        }

        MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Qp ", &ssl->handshake->ecdh_ctx.Qp );

        if( ( ret = mbedtls_ecdh_calc_secret( &ssl->handshake->ecdh_ctx,
                                      &ssl->handshake->pmslen,
                                       ssl->handshake->premaster,
                                       MBEDTLS_MPI_MAX_SIZE,
                                       ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_calc_secret", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS );
        }

        MBEDTLS_SSL_DEBUG_MPI( 3, "ECDH: z  ", &ssl->handshake->ecdh_ctx.z );
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK )
    {
        if( ( ret = ssl_parse_client_psk_identity( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_psk_identity" ), ret );
            return( ret );
        }

        if( p != end )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
        }

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK )
    {
        if( ( ret = ssl_parse_client_psk_identity( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_psk_identity" ), ret );
            return( ret );
        }

        if( ( ret = ssl_parse_encrypted_pms( ssl, p, end, 2 ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_encrypted_pms" ), ret );
            return( ret );
        }

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK )
    {
        if( ( ret = ssl_parse_client_psk_identity( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_psk_identity" ), ret );
            return( ret );
        }
        if( ( ret = ssl_parse_client_dh_public( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_dh_public" ), ret );
            return( ret );
        }

        if( p != end )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
        }

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK )
    {
        if( ( ret = ssl_parse_client_psk_identity( ssl, &p, end ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_client_psk_identity" ), ret );
            return( ret );
        }

        if( ( ret = mbedtls_ecdh_read_public( &ssl->handshake->ecdh_ctx,
                                       p, end - p ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_read_public", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP );
        }

        MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Qp ", &ssl->handshake->ecdh_ctx.Qp );

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA )
    {
        if( ( ret = ssl_parse_encrypted_pms( ssl, p, end, 0 ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, ( "ssl_parse_parse_encrypted_pms_secret" ), ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_RSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE )
    {
        ret = mbedtls_ecjpake_read_round_two( &ssl->handshake->ecjpake_ctx,
                                              p, end - p );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_read_round_two", ret );
            return( MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE );
        }

        ret = mbedtls_ecjpake_derive_secret( &ssl->handshake->ecjpake_ctx,
                ssl->handshake->premaster, 32, &ssl->handshake->pmslen,
                ssl->conf->f_rng, ssl->conf->p_rng );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_derive_secret", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    if( ( ret = mbedtls_ssl_derive_keys( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_derive_keys", ret );
        return( ret );
    }

    ssl->state++;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse client key exchange" ) );

    return( 0 );
}
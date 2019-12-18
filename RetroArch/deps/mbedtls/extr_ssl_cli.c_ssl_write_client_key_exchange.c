#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {unsigned char* out_msg; size_t out_msglen; int /*<<< orphan*/  state; int /*<<< orphan*/  out_msgtype; TYPE_2__* conf; TYPE_3__* handshake; TYPE_1__* transform_negotiate; } ;
typedef  TYPE_4__ mbedtls_ssl_context ;
struct TYPE_21__ {scalar_t__ key_exchange; } ;
typedef  TYPE_5__ mbedtls_ssl_ciphersuite_t ;
struct TYPE_15__ {int /*<<< orphan*/  Q; int /*<<< orphan*/  z; } ;
struct TYPE_16__ {size_t len; int /*<<< orphan*/  P; int /*<<< orphan*/  K; int /*<<< orphan*/  GX; int /*<<< orphan*/  X; } ;
struct TYPE_19__ {int /*<<< orphan*/  pmslen; int /*<<< orphan*/  premaster; int /*<<< orphan*/  ecjpake_ctx; TYPE_11__ ecdh_ctx; TYPE_13__ dhm_ctx; } ;
struct TYPE_18__ {size_t psk_identity_len; int /*<<< orphan*/  p_rng; int /*<<< orphan*/  f_rng; int /*<<< orphan*/ * psk_identity; int /*<<< orphan*/ * psk; } ;
struct TYPE_17__ {TYPE_5__* ciphersuite_info; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED ; 
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
 unsigned char MBEDTLS_SSL_HS_CLIENT_KEY_EXCHANGE ; 
 size_t MBEDTLS_SSL_MAX_CONTENT_LEN ; 
 int /*<<< orphan*/  MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int mbedtls_dhm_calc_secret (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_dhm_make_public (TYPE_13__*,int,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecdh_calc_secret (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecdh_make_public (TYPE_11__*,size_t*,unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecjpake_derive_secret (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecjpake_write_round_two (int /*<<< orphan*/ *,unsigned char*,size_t,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mbedtls_mpi_size (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_uses_psk (TYPE_5__ const*) ; 
 int mbedtls_ssl_psk_derive_premaster (TYPE_4__*,scalar_t__) ; 
 int mbedtls_ssl_write_record (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,size_t) ; 
 int ssl_write_encrypted_pms (TYPE_4__*,size_t,size_t*,int) ; 

__attribute__((used)) static int ssl_write_client_key_exchange( mbedtls_ssl_context *ssl )
{
    int ret;
    size_t i, n;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info =
        ssl->transform_negotiate->ciphersuite_info;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write client key exchange" ) );

#if defined(MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_RSA )
    {
        /*
         * DHM key exchange -- send G^X mod P
         */
        n = ssl->handshake->dhm_ctx.len;

        ssl->out_msg[4] = (unsigned char)( n >> 8 );
        ssl->out_msg[5] = (unsigned char)( n      );
        i = 6;

        ret = mbedtls_dhm_make_public( &ssl->handshake->dhm_ctx,
                                (int) mbedtls_mpi_size( &ssl->handshake->dhm_ctx.P ),
                               &ssl->out_msg[i], n,
                                ssl->conf->f_rng, ssl->conf->p_rng );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_make_public", ret );
            return( ret );
        }

        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: X ", &ssl->handshake->dhm_ctx.X  );
        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: GX", &ssl->handshake->dhm_ctx.GX );

        if( ( ret = mbedtls_dhm_calc_secret( &ssl->handshake->dhm_ctx,
                                      ssl->handshake->premaster,
                                      MBEDTLS_PREMASTER_SIZE,
                                     &ssl->handshake->pmslen,
                                      ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_calc_secret", ret );
            return( ret );
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
        /*
         * ECDH key exchange -- send client public value
         */
        i = 4;

        ret = mbedtls_ecdh_make_public( &ssl->handshake->ecdh_ctx,
                                &n,
                                &ssl->out_msg[i], 1000,
                                ssl->conf->f_rng, ssl->conf->p_rng );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_make_public", ret );
            return( ret );
        }

        MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Q", &ssl->handshake->ecdh_ctx.Q );

        if( ( ret = mbedtls_ecdh_calc_secret( &ssl->handshake->ecdh_ctx,
                                      &ssl->handshake->pmslen,
                                       ssl->handshake->premaster,
                                       MBEDTLS_MPI_MAX_SIZE,
                                       ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_calc_secret", ret );
            return( ret );
        }

        MBEDTLS_SSL_DEBUG_MPI( 3, "ECDH: z", &ssl->handshake->ecdh_ctx.z );
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED)
    if( mbedtls_ssl_ciphersuite_uses_psk( ciphersuite_info ) )
    {
        /*
         * opaque psk_identity<0..2^16-1>;
         */
        if( ssl->conf->psk == NULL || ssl->conf->psk_identity == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "got no private key for PSK" ) );
            return( MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED );
        }

        i = 4;
        n = ssl->conf->psk_identity_len;

        if( i + 2 + n > MBEDTLS_SSL_MAX_CONTENT_LEN )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "psk identity too long or "
                                        "SSL buffer too short" ) );
            return( MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL );
        }

        ssl->out_msg[i++] = (unsigned char)( n >> 8 );
        ssl->out_msg[i++] = (unsigned char)( n      );

        memcpy( ssl->out_msg + i, ssl->conf->psk_identity, ssl->conf->psk_identity_len );
        i += ssl->conf->psk_identity_len;

#if defined(MBEDTLS_KEY_EXCHANGE_PSK_ENABLED)
        if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_PSK )
        {
            n = 0;
        }
        else
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED)
        if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA_PSK )
        {
            if( ( ret = ssl_write_encrypted_pms( ssl, i, &n, 2 ) ) != 0 )
                return( ret );
        }
        else
#endif
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)
        if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK )
        {
            /*
             * ClientDiffieHellmanPublic public (DHM send G^X mod P)
             */
            n = ssl->handshake->dhm_ctx.len;

            if( i + 2 + n > MBEDTLS_SSL_MAX_CONTENT_LEN )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "psk identity or DHM size too long"
                                            " or SSL buffer too short" ) );
                return( MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL );
            }

            ssl->out_msg[i++] = (unsigned char)( n >> 8 );
            ssl->out_msg[i++] = (unsigned char)( n      );

            ret = mbedtls_dhm_make_public( &ssl->handshake->dhm_ctx,
                    (int) mbedtls_mpi_size( &ssl->handshake->dhm_ctx.P ),
                    &ssl->out_msg[i], n,
                    ssl->conf->f_rng, ssl->conf->p_rng );
            if( ret != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_make_public", ret );
                return( ret );
            }
        }
        else
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
        if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK )
        {
            /*
             * ClientECDiffieHellmanPublic public;
             */
            ret = mbedtls_ecdh_make_public( &ssl->handshake->ecdh_ctx, &n,
                    &ssl->out_msg[i], MBEDTLS_SSL_MAX_CONTENT_LEN - i,
                    ssl->conf->f_rng, ssl->conf->p_rng );
            if( ret != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_make_public", ret );
                return( ret );
            }

            MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Q", &ssl->handshake->ecdh_ctx.Q );
        }
        else
#endif /* MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED */
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
            return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
        }

        if( ( ret = mbedtls_ssl_psk_derive_premaster( ssl,
                        ciphersuite_info->key_exchange ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_psk_derive_premaster", ret );
            return( ret );
        }
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_RSA_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_RSA )
    {
        i = 4;
        if( ( ret = ssl_write_encrypted_pms( ssl, i, &n, 0 ) ) != 0 )
            return( ret );
    }
    else
#endif /* MBEDTLS_KEY_EXCHANGE_RSA_ENABLED */
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE )
    {
        i = 4;

        ret = mbedtls_ecjpake_write_round_two( &ssl->handshake->ecjpake_ctx,
                ssl->out_msg + i, MBEDTLS_SSL_MAX_CONTENT_LEN - i, &n,
                ssl->conf->f_rng, ssl->conf->p_rng );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_write_round_two", ret );
            return( ret );
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
#endif /* MBEDTLS_KEY_EXCHANGE_RSA_ENABLED */
    {
        ((void) ciphersuite_info);
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }

    ssl->out_msglen  = i + n;
    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_CLIENT_KEY_EXCHANGE;

    ssl->state++;

    if( ( ret = mbedtls_ssl_write_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_write_record", ret );
        return( ret );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write client key exchange" ) );

    return( 0 );
}
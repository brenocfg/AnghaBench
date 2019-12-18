#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;
typedef  struct TYPE_21__   TYPE_18__ ;
typedef  struct TYPE_20__   TYPE_17__ ;

/* Type definitions */
struct TYPE_26__ {unsigned char* out_msg; scalar_t__ minor_ver; int out_msglen; int /*<<< orphan*/  state; int /*<<< orphan*/  out_msgtype; TYPE_3__* conf; TYPE_2__* handshake; TYPE_1__* transform_negotiate; } ;
typedef  TYPE_4__ mbedtls_ssl_context ;
struct TYPE_27__ {scalar_t__ key_exchange; } ;
typedef  TYPE_5__ mbedtls_ssl_ciphersuite_t ;
typedef  int /*<<< orphan*/  mbedtls_sha1_context ;
typedef  scalar_t__ mbedtls_pk_type_t ;
typedef  scalar_t__ mbedtls_md_type_t ;
typedef  int /*<<< orphan*/  mbedtls_md_info_t ;
typedef  int /*<<< orphan*/  mbedtls_md_context_t ;
typedef  int /*<<< orphan*/  mbedtls_md5_context ;
typedef  scalar_t__ mbedtls_ecp_group_id ;
struct TYPE_28__ {scalar_t__ const grp_id; int /*<<< orphan*/  name; } ;
typedef  TYPE_6__ mbedtls_ecp_curve_info ;
struct TYPE_20__ {int /*<<< orphan*/ * p; } ;
struct TYPE_25__ {scalar_t__* curve_list; int /*<<< orphan*/  p_rng; int /*<<< orphan*/  f_rng; TYPE_17__ dhm_G; TYPE_17__ dhm_P; } ;
struct TYPE_21__ {int /*<<< orphan*/  Q; int /*<<< orphan*/  grp; } ;
struct TYPE_22__ {int /*<<< orphan*/  GX; int /*<<< orphan*/  G; int /*<<< orphan*/  P; int /*<<< orphan*/  X; } ;
struct TYPE_24__ {unsigned char* randbytes; int /*<<< orphan*/  hash_algs; TYPE_18__ ecdh_ctx; TYPE_6__** curves; TYPE_19__ dhm_ctx; int /*<<< orphan*/  ecjpake_ctx; } ;
struct TYPE_23__ {TYPE_5__* ciphersuite_info; } ;

/* Variables and functions */
 scalar_t__ const MBEDTLS_ECP_DP_NONE ; 
 int MBEDTLS_ERR_SSL_BAD_INPUT_DATA ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN ; 
 int MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_DHE_PSK ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECDHE_PSK ; 
 scalar_t__ MBEDTLS_KEY_EXCHANGE_ECJPAKE ; 
 scalar_t__ MBEDTLS_MD_NONE ; 
 scalar_t__ MBEDTLS_MD_SHA1 ; 
 scalar_t__ MBEDTLS_PK_NONE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_BUF (int,char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_ECP (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MPI (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 unsigned char MBEDTLS_SSL_HS_SERVER_KEY_EXCHANGE ; 
 int MBEDTLS_SSL_MAX_CONTENT_LEN ; 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_3 ; 
 int /*<<< orphan*/  MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int mbedtls_dhm_make_params (TYPE_19__*,int,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecdh_make_params (TYPE_18__*,size_t*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecjpake_write_round_two (int /*<<< orphan*/ *,unsigned char*,int,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_ecp_group_load (int /*<<< orphan*/ *,scalar_t__ const) ; 
 int /*<<< orphan*/  mbedtls_md5_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md5_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  mbedtls_md_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_md_get_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbedtls_md_info_from_type (scalar_t__) ; 
 int /*<<< orphan*/  mbedtls_md_init (int /*<<< orphan*/ *) ; 
 int mbedtls_md_setup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_md_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int mbedtls_mpi_copy (int /*<<< orphan*/ *,TYPE_17__*) ; 
 scalar_t__ mbedtls_mpi_size (int /*<<< orphan*/ *) ; 
 int mbedtls_pk_sign (int /*<<< orphan*/ *,scalar_t__,unsigned char*,unsigned int,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_sha1_finish (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_sha1_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_starts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_sha1_update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_no_pfs (TYPE_5__ const*) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_uses_dhe (TYPE_5__ const*) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_uses_ecdh (TYPE_5__ const*) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_uses_ecdhe (TYPE_5__ const*) ; 
 scalar_t__ mbedtls_ssl_ciphersuite_uses_server_signature (TYPE_5__ const*) ; 
 scalar_t__ mbedtls_ssl_get_ciphersuite_sig_pk_alg (TYPE_5__ const*) ; 
 int /*<<< orphan*/  mbedtls_ssl_hash_from_md_alg (scalar_t__) ; 
 int /*<<< orphan*/ * mbedtls_ssl_own_key (TYPE_4__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_sig_from_pk_alg (scalar_t__) ; 
 scalar_t__ mbedtls_ssl_sig_hash_set_find (int /*<<< orphan*/ *,scalar_t__) ; 
 int mbedtls_ssl_write_record (TYPE_4__*) ; 
 int /*<<< orphan*/  ssl_srv_get_ecdh_params_from_cert (TYPE_4__*) ; 

__attribute__((used)) static int ssl_write_server_key_exchange( mbedtls_ssl_context *ssl )
{
    int ret;
    size_t n = 0;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info =
                            ssl->transform_negotiate->ciphersuite_info;

#if defined(MBEDTLS_KEY_EXCHANGE__SOME_PFS__ENABLED)
    unsigned char *p = ssl->out_msg + 4;
    size_t len;
#if defined(MBEDTLS_KEY_EXCHANGE__WITH_SERVER_SIGNATURE__ENABLED)
    unsigned char *dig_signed = p;
    size_t dig_signed_len = 0;
#endif /* MBEDTLS_KEY_EXCHANGE__WITH_SERVER_SIGNATURE__ENABLED */
#endif /* MBEDTLS_KEY_EXCHANGE__SOME_PFS__ENABLED */

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> write server key exchange" ) );

    /*
     *
     * Part 1: Extract static ECDH parameters and abort
     *         if ServerKeyExchange not needed.
     *
     */

    /* For suites involving ECDH, extract DH parameters
     * from certificate at this point. */
#if defined(MBEDTLS_KEY_EXCHANGE__SOME__ECDH_ENABLED)
    if( mbedtls_ssl_ciphersuite_uses_ecdh( ciphersuite_info ) )
    {
        ssl_srv_get_ecdh_params_from_cert( ssl );
    }
#endif /* MBEDTLS_KEY_EXCHANGE__SOME__ECDH_ENABLED */

    /* Key exchanges not involving ephemeral keys don't use
     * ServerKeyExchange, so end here. */
#if defined(MBEDTLS_KEY_EXCHANGE__SOME_NON_PFS__ENABLED)
    if( mbedtls_ssl_ciphersuite_no_pfs( ciphersuite_info ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip write server key exchange" ) );
        ssl->state++;
        return( 0 );
    }
#endif /* MBEDTLS_KEY_EXCHANGE__NON_PFS__ENABLED */

    /*
     *
     * Part 2: Provide key exchange parameters for chosen ciphersuite.
     *
     */

    /*
     * - ECJPAKE key exchanges
     */
#if defined(MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECJPAKE )
    {
        const unsigned char *end = ssl->out_msg + MBEDTLS_SSL_MAX_CONTENT_LEN;

        ret = mbedtls_ecjpake_write_round_two( &ssl->handshake->ecjpake_ctx,
                p, end - p, &len, ssl->conf->f_rng, ssl->conf->p_rng );
        if( ret != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecjpake_write_round_two", ret );
            return( ret );
        }

        p += len;
        n += len;
    }
#endif /* MBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED */

    /*
     * For (EC)DHE key exchanges with PSK, parameters are prefixed by support
     * identity hint (RFC 4279, Sec. 3). Until someone needs this feature,
     * we use empty support identity hints here.
     **/
#if defined(MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED)   || \
    defined(MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED)
    if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_DHE_PSK ||
        ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_PSK )
    {
        *(p++) = 0x00;
        *(p++) = 0x00;

        n += 2;
    }
#endif /* MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED ||
          MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED */

    /*
     * - DHE key exchanges
     */
#if defined(MBEDTLS_KEY_EXCHANGE__SOME__DHE_ENABLED)
    if( mbedtls_ssl_ciphersuite_uses_dhe( ciphersuite_info ) )
    {
        if( ssl->conf->dhm_P.p == NULL || ssl->conf->dhm_G.p == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "no DH parameters set" ) );
            return( MBEDTLS_ERR_SSL_BAD_INPUT_DATA );
        }

        /*
         * Ephemeral DH parameters:
         *
         * struct {
         *     opaque dh_p<1..2^16-1>;
         *     opaque dh_g<1..2^16-1>;
         *     opaque dh_Ys<1..2^16-1>;
         * } ServerDHParams;
         */
        if( ( ret = mbedtls_mpi_copy( &ssl->handshake->dhm_ctx.P, &ssl->conf->dhm_P ) ) != 0 ||
            ( ret = mbedtls_mpi_copy( &ssl->handshake->dhm_ctx.G, &ssl->conf->dhm_G ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_mpi_copy", ret );
            return( ret );
        }

        if( ( ret = mbedtls_dhm_make_params( &ssl->handshake->dhm_ctx,
                        (int) mbedtls_mpi_size( &ssl->handshake->dhm_ctx.P ),
                        p, &len, ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_dhm_make_params", ret );
            return( ret );
        }

#if defined(MBEDTLS_KEY_EXCHANGE__WITH_SERVER_SIGNATURE__ENABLED)
        dig_signed = p;
        dig_signed_len = len;
#endif

        p += len;
        n += len;

        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: X ", &ssl->handshake->dhm_ctx.X  );
        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: P ", &ssl->handshake->dhm_ctx.P  );
        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: G ", &ssl->handshake->dhm_ctx.G  );
        MBEDTLS_SSL_DEBUG_MPI( 3, "DHM: GX", &ssl->handshake->dhm_ctx.GX );
    }
#endif /* MBEDTLS_KEY_EXCHANGE__SOME__DHE_ENABLED */

    /*
     * - ECDHE key exchanges
     */
#if defined(MBEDTLS_KEY_EXCHANGE__SOME__ECDHE_ENABLED)
    if( mbedtls_ssl_ciphersuite_uses_ecdhe( ciphersuite_info ) )
    {
        /*
         * Ephemeral ECDH parameters:
         *
         * struct {
         *     ECParameters curve_params;
         *     ECPoint      public;
         * } ServerECDHParams;
         */
        const mbedtls_ecp_curve_info **curve = NULL;
        const mbedtls_ecp_group_id *gid;

        /* Match our preference list against the offered curves */
        for( gid = ssl->conf->curve_list; *gid != MBEDTLS_ECP_DP_NONE; gid++ )
            for( curve = ssl->handshake->curves; *curve != NULL; curve++ )
                if( (*curve)->grp_id == *gid )
                    goto curve_matching_done;

curve_matching_done:
        if( curve == NULL || *curve == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "no matching curve for ECDHE" ) );
            return( MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN );
        }

        MBEDTLS_SSL_DEBUG_MSG( 2, ( "ECDHE curve: %s", (*curve)->name ) );

        if( ( ret = mbedtls_ecp_group_load( &ssl->handshake->ecdh_ctx.grp,
                                       (*curve)->grp_id ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecp_group_load", ret );
            return( ret );
        }

        if( ( ret = mbedtls_ecdh_make_params( &ssl->handshake->ecdh_ctx, &len,
                                      p, MBEDTLS_SSL_MAX_CONTENT_LEN - n,
                                      ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ecdh_make_params", ret );
            return( ret );
        }

#if defined(MBEDTLS_KEY_EXCHANGE__WITH_SERVER_SIGNATURE__ENABLED)
        dig_signed     = p;
        dig_signed_len = len;
#endif

        p += len;
        n += len;

        MBEDTLS_SSL_DEBUG_ECP( 3, "ECDH: Q ", &ssl->handshake->ecdh_ctx.Q );
    }
#endif /* MBEDTLS_KEY_EXCHANGE__SOME__ECDHE_ENABLED */

    /*
     *
     * Part 3: For key exchanges involving the server signing the
     *         exchange parameters, compute and add the signature here.
     *
     */
#if defined(MBEDTLS_KEY_EXCHANGE__WITH_SERVER_SIGNATURE__ENABLED)
    if( mbedtls_ssl_ciphersuite_uses_server_signature( ciphersuite_info ) )
    {
        size_t signature_len = 0;
        unsigned int hashlen = 0;
        unsigned char hash[64];

        /*
         * 3.1: Choose hash algorithm:
         * A: For TLS 1.2, obey signature-hash-algorithm extension
         *    to choose appropriate hash.
         * B: For SSL3, TLS1.0, TLS1.1 and ECDHE_ECDSA, use SHA1
         *    (RFC 4492, Sec. 5.4)
         * C: Otherwise, use MD5 + SHA1 (RFC 4346, Sec. 7.4.3)
         */

        mbedtls_md_type_t md_alg;

#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
        mbedtls_pk_type_t sig_alg =
            mbedtls_ssl_get_ciphersuite_sig_pk_alg( ciphersuite_info );
        if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
        {
            /* A: For TLS 1.2, obey signature-hash-algorithm extension
             *    (RFC 5246, Sec. 7.4.1.4.1). */
            if( sig_alg == MBEDTLS_PK_NONE ||
                ( md_alg = mbedtls_ssl_sig_hash_set_find( &ssl->handshake->hash_algs,
                                                          sig_alg ) ) == MBEDTLS_MD_NONE )
            {
                MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
                /* (... because we choose a cipher suite
                 *      only if there is a matching hash.) */
                return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
            }
        }
        else
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
        if( ciphersuite_info->key_exchange == MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA )
        {
            /* B: Default hash SHA1 */
            md_alg = MBEDTLS_MD_SHA1;
        }
        else
#endif /* MBEDTLS_SSL_PROTO_SSL3 || MBEDTLS_SSL_PROTO_TLS1 || \
          MBEDTLS_SSL_PROTO_TLS1_1 */
        {
            /* C: MD5 + SHA1 */
            md_alg = MBEDTLS_MD_NONE;
        }

        MBEDTLS_SSL_DEBUG_MSG( 3, ( "pick hash algorithm %d for signing", md_alg ) );

        /*
         * 3.2: Compute the hash to be signed
         */
#if defined(MBEDTLS_SSL_PROTO_SSL3) || defined(MBEDTLS_SSL_PROTO_TLS1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_1)
        if( md_alg == MBEDTLS_MD_NONE )
        {
            mbedtls_md5_context mbedtls_md5;
            mbedtls_sha1_context mbedtls_sha1;

            mbedtls_md5_init(  &mbedtls_md5  );
            mbedtls_sha1_init( &mbedtls_sha1 );

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
            mbedtls_md5_update( &mbedtls_md5, ssl->handshake->randbytes,  64 );
            mbedtls_md5_update( &mbedtls_md5, dig_signed, dig_signed_len );
            mbedtls_md5_finish( &mbedtls_md5, hash );

            mbedtls_sha1_starts( &mbedtls_sha1 );
            mbedtls_sha1_update( &mbedtls_sha1, ssl->handshake->randbytes,  64 );
            mbedtls_sha1_update( &mbedtls_sha1, dig_signed, dig_signed_len );
            mbedtls_sha1_finish( &mbedtls_sha1, hash + 16 );

            hashlen = 36;

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
            const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type( md_alg );

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
            if( ( ret = mbedtls_md_setup( &ctx, md_info, 0 ) ) != 0 )
            {
                MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_md_setup", ret );
                return( ret );
            }

            mbedtls_md_starts( &ctx );
            mbedtls_md_update( &ctx, ssl->handshake->randbytes, 64 );
            mbedtls_md_update( &ctx, dig_signed, dig_signed_len );
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

        /*
         * 3.3: Compute and add the signature
         */
        if( mbedtls_ssl_own_key( ssl ) == NULL )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "got no private key" ) );
            return( MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED );
        }

#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
        if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
        {
            /*
             * For TLS 1.2, we need to specify signature and hash algorithm
             * explicitly through a prefix to the signature.
             *
             * struct {
             *    HashAlgorithm hash;
             *    SignatureAlgorithm signature;
             * } SignatureAndHashAlgorithm;
             *
             * struct {
             *    SignatureAndHashAlgorithm algorithm;
             *    opaque signature<0..2^16-1>;
             * } DigitallySigned;
             *
             */

            *(p++) = mbedtls_ssl_hash_from_md_alg( md_alg );
            *(p++) = mbedtls_ssl_sig_from_pk_alg( sig_alg );

            n += 2;
        }
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */

        if( ( ret = mbedtls_pk_sign( mbedtls_ssl_own_key( ssl ), md_alg, hash, hashlen,
                        p + 2 , &signature_len, ssl->conf->f_rng, ssl->conf->p_rng ) ) != 0 )
        {
            MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_pk_sign", ret );
            return( ret );
        }

        *(p++) = (unsigned char)( signature_len >> 8 );
        *(p++) = (unsigned char)( signature_len      );
        n += 2;

        MBEDTLS_SSL_DEBUG_BUF( 3, "my signature", p, signature_len );

        n += signature_len;
    }
#endif /* MBEDTLS_KEY_EXCHANGE__WITH_SERVER_SIGNATURE__ENABLED */

    /* Done with actual work; add header and send. */

    ssl->out_msglen  = 4 + n;
    ssl->out_msgtype = MBEDTLS_SSL_MSG_HANDSHAKE;
    ssl->out_msg[0]  = MBEDTLS_SSL_HS_SERVER_KEY_EXCHANGE;

    ssl->state++;

    if( ( ret = mbedtls_ssl_write_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_write_record", ret );
        return( ret );
    }

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= write server key exchange" ) );

    return( 0 );
}
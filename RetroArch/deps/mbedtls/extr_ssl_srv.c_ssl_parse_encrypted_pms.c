#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  peer_pms ;
struct TYPE_8__ {scalar_t__ minor_ver; TYPE_2__* handshake; TYPE_1__* conf; } ;
typedef  TYPE_3__ mbedtls_ssl_context ;
typedef  int /*<<< orphan*/  len ;
typedef  int /*<<< orphan*/  fake_pms ;
struct TYPE_7__ {unsigned char* premaster; int pmslen; int /*<<< orphan*/  max_minor_ver; int /*<<< orphan*/  max_major_ver; } ;
struct TYPE_6__ {int (* f_rng ) (int /*<<< orphan*/ ,unsigned char*,int) ;int /*<<< orphan*/  p_rng; int /*<<< orphan*/  transport; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE ; 
 int MBEDTLS_ERR_SSL_INTERNAL_ERROR ; 
 int MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED ; 
 int /*<<< orphan*/  MBEDTLS_PK_RSA ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_0 ; 
 int /*<<< orphan*/  mbedtls_pk_can_do (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbedtls_pk_decrypt (int /*<<< orphan*/ ,unsigned char const*,size_t,unsigned char*,size_t*,int,int (*) (int /*<<< orphan*/ ,unsigned char*,int),int /*<<< orphan*/ ) ; 
 size_t mbedtls_pk_get_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_own_key (TYPE_3__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_write_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int ssl_parse_encrypted_pms( mbedtls_ssl_context *ssl,
                                    const unsigned char *p,
                                    const unsigned char *end,
                                    size_t pms_offset )
{
    int ret;
    size_t len = mbedtls_pk_get_len( mbedtls_ssl_own_key( ssl ) );
    unsigned char *pms = ssl->handshake->premaster + pms_offset;
    unsigned char ver[2];
    unsigned char fake_pms[48], peer_pms[48];
    unsigned char mask;
    size_t i, peer_pmslen;
    unsigned int diff;

    if( ! mbedtls_pk_can_do( mbedtls_ssl_own_key( ssl ), MBEDTLS_PK_RSA ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "got no RSA private key" ) );
        return( MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED );
    }

    /*
     * Decrypt the premaster using own private RSA key
     */
#if defined(MBEDTLS_SSL_PROTO_TLS1) || defined(MBEDTLS_SSL_PROTO_TLS1_1) || \
    defined(MBEDTLS_SSL_PROTO_TLS1_2)
    if( ssl->minor_ver != MBEDTLS_SSL_MINOR_VERSION_0 )
    {
        if( *p++ != ( ( len >> 8 ) & 0xFF ) ||
            *p++ != ( ( len      ) & 0xFF ) )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
            return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
        }
    }
#endif

    if( p + len != end )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE );
    }

    mbedtls_ssl_write_version( ssl->handshake->max_major_ver,
                       ssl->handshake->max_minor_ver,
                       ssl->conf->transport, ver );

    /*
     * Protection against Bleichenbacher's attack: invalid PKCS#1 v1.5 padding
     * must not cause the connection to end immediately; instead, send a
     * bad_record_mac later in the handshake.
     * Also, avoid data-dependant branches here to protect against
     * timing-based variants.
     */
    ret = ssl->conf->f_rng( ssl->conf->p_rng, fake_pms, sizeof( fake_pms ) );
    if( ret != 0 )
        return( ret );

    ret = mbedtls_pk_decrypt( mbedtls_ssl_own_key( ssl ), p, len,
                      peer_pms, &peer_pmslen,
                      sizeof( peer_pms ),
                      ssl->conf->f_rng, ssl->conf->p_rng );

    diff  = (unsigned int) ret;
    diff |= peer_pmslen ^ 48;
    diff |= peer_pms[0] ^ ver[0];
    diff |= peer_pms[1] ^ ver[1];

#if defined(MBEDTLS_SSL_DEBUG_ALL)
    if( diff != 0 )
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client key exchange message" ) );
#endif

    if( sizeof( ssl->handshake->premaster ) < pms_offset ||
        sizeof( ssl->handshake->premaster ) - pms_offset < 48 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "should never happen" ) );
        return( MBEDTLS_ERR_SSL_INTERNAL_ERROR );
    }
    ssl->handshake->pmslen = 48;

    /* mask = diff ? 0xff : 0x00 using bit operations to avoid branches */
    /* MSVC has a warning about unary minus on unsigned, but this is
     * well-defined and precisely what we want to do here */
#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4146 )
#endif
    mask = - ( ( diff | - diff ) >> ( sizeof( unsigned int ) * 8 - 1 ) );
#if defined(_MSC_VER)
#pragma warning( pop )
#endif

    for( i = 0; i < ssl->handshake->pmslen; i++ )
        pms[i] = ( mask & fake_pms[i] ) | ( (~mask) & peer_pms[i] );

    return( 0 );
}
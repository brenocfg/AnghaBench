#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* handshake; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
typedef  int /*<<< orphan*/  mbedtls_pk_type_t ;
typedef  scalar_t__ mbedtls_md_type_t ;
struct TYPE_6__ {int /*<<< orphan*/  hash_algs; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO ; 
 scalar_t__ MBEDTLS_MD_NONE ; 
 int /*<<< orphan*/  MBEDTLS_PK_NONE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 scalar_t__ mbedtls_ssl_check_sig_hash (TYPE_2__*,scalar_t__) ; 
 scalar_t__ mbedtls_ssl_md_alg_from_hash (unsigned char const) ; 
 int /*<<< orphan*/  mbedtls_ssl_pk_alg_from_sig (unsigned char const) ; 
 int /*<<< orphan*/  mbedtls_ssl_send_alert_message (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_sig_hash_set_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ssl_parse_signature_algorithms_ext( mbedtls_ssl_context *ssl,
                                               const unsigned char *buf,
                                               size_t len )
{
    size_t sig_alg_list_size;

    const unsigned char *p;
    const unsigned char *end = buf + len;

    mbedtls_md_type_t md_cur;
    mbedtls_pk_type_t sig_cur;

    sig_alg_list_size = ( ( buf[0] << 8 ) | ( buf[1] ) );
    if( sig_alg_list_size + 2 != len ||
        sig_alg_list_size % 2 != 0 )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad client hello message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO );
    }

    /* Currently we only guarantee signing the ServerKeyExchange message according
     * to the constraints specified in this extension (see above), so it suffices
     * to remember only one suitable hash for each possible signature algorithm.
     *
     * This will change when we also consider certificate signatures,
     * in which case we will need to remember the whole signature-hash
     * pair list from the extension.
     */

    for( p = buf + 2; p < end; p += 2 )
    {
        /* Silently ignore unknown signature or hash algorithms. */

        if( ( sig_cur = mbedtls_ssl_pk_alg_from_sig( p[1] ) ) == MBEDTLS_PK_NONE )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, signature_algorithm ext"
                                        " unknown sig alg encoding %d", p[1] ) );
            continue;
        }

        /* Check if we support the hash the user proposes */
        md_cur = mbedtls_ssl_md_alg_from_hash( p[0] );
        if( md_cur == MBEDTLS_MD_NONE )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, signature_algorithm ext:"
                                        " unknown hash alg encoding %d", p[0] ) );
            continue;
        }

        if( mbedtls_ssl_check_sig_hash( ssl, md_cur ) == 0 )
        {
            mbedtls_ssl_sig_hash_set_add( &ssl->handshake->hash_algs, sig_cur, md_cur );
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, signature_algorithm ext:"
                                        " match sig %d and hash %d",
                                        sig_cur, md_cur ) );
        }
        else
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello v3, signature_algorithm ext: "
                                        "hash alg %d not supported", md_cur ) );
        }
    }

    return( 0 );
}
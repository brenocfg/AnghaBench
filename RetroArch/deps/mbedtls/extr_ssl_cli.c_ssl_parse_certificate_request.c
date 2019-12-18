#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ in_msgtype; int client_auth; scalar_t__* in_msg; int keep_current_message; int in_hslen; scalar_t__ minor_ver; int /*<<< orphan*/  state; TYPE_1__* transform_negotiate; } ;
typedef  TYPE_2__ mbedtls_ssl_context ;
typedef  int /*<<< orphan*/  mbedtls_ssl_ciphersuite_t ;
struct TYPE_7__ {int /*<<< orphan*/ * ciphersuite_info; } ;

/* Variables and functions */
 int MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST ; 
 int MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_LEVEL_FATAL ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_MSG (int,char*) ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DEBUG_RET (int,char*,int) ; 
 scalar_t__ MBEDTLS_SSL_HS_CERTIFICATE_REQUEST ; 
 scalar_t__ MBEDTLS_SSL_MINOR_VERSION_3 ; 
 scalar_t__ MBEDTLS_SSL_MSG_HANDSHAKE ; 
 int /*<<< orphan*/  mbedtls_ssl_ciphersuite_cert_req_allowed (int /*<<< orphan*/  const*) ; 
 int mbedtls_ssl_hs_hdr_len (TYPE_2__*) ; 
 int mbedtls_ssl_read_record (TYPE_2__*) ; 
 int /*<<< orphan*/  mbedtls_ssl_send_alert_message (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssl_parse_certificate_request( mbedtls_ssl_context *ssl )
{
    int ret;
    unsigned char *buf;
    size_t n = 0;
    size_t cert_type_len = 0, dn_len = 0;
    const mbedtls_ssl_ciphersuite_t *ciphersuite_info =
        ssl->transform_negotiate->ciphersuite_info;

    MBEDTLS_SSL_DEBUG_MSG( 2, ( "=> parse certificate request" ) );

    if( ! mbedtls_ssl_ciphersuite_cert_req_allowed( ciphersuite_info ) )
    {
        MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= skip parse certificate request" ) );
        ssl->state++;
        return( 0 );
    }

    if( ( ret = mbedtls_ssl_read_record( ssl ) ) != 0 )
    {
        MBEDTLS_SSL_DEBUG_RET( 1, "mbedtls_ssl_read_record", ret );
        return( ret );
    }

    if( ssl->in_msgtype != MBEDTLS_SSL_MSG_HANDSHAKE )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate request message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_UNEXPECTED_MESSAGE );
        return( MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE );
    }

    ssl->state++;
    ssl->client_auth = ( ssl->in_msg[0] == MBEDTLS_SSL_HS_CERTIFICATE_REQUEST );

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "got %s certificate request",
                        ssl->client_auth ? "a" : "no" ) );

    if( ssl->client_auth == 0 )
    {
        /* Current message is probably the ServerHelloDone */
        ssl->keep_current_message = 1;
        goto exit;
    }

    /*
     *  struct {
     *      ClientCertificateType certificate_types<1..2^8-1>;
     *      SignatureAndHashAlgorithm
     *        supported_signature_algorithms<2^16-1>; -- TLS 1.2 only
     *      DistinguishedName certificate_authorities<0..2^16-1>;
     *  } CertificateRequest;
     *
     *  Since we only support a single certificate on clients, let's just
     *  ignore all the information that's supposed to help us pick a
     *  certificate.
     *
     *  We could check that our certificate matches the request, and bail out
     *  if it doesn't, but it's simpler to just send the certificate anyway,
     *  and give the server the opportunity to decide if it should terminate
     *  the connection when it doesn't like our certificate.
     *
     *  Same goes for the hash in TLS 1.2's signature_algorithms: at this
     *  point we only have one hash available (see comments in
     *  write_certificate_verify), so let's just use what we have.
     *
     *  However, we still minimally parse the message to check it is at least
     *  superficially sane.
     */
    buf = ssl->in_msg;

    /* certificate_types */
    cert_type_len = buf[mbedtls_ssl_hs_hdr_len( ssl )];
    n = cert_type_len;

    if( ssl->in_hslen < mbedtls_ssl_hs_hdr_len( ssl ) + 2 + n )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate request message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST );
    }

    /* supported_signature_algorithms */
#if defined(MBEDTLS_SSL_PROTO_TLS1_2)
    if( ssl->minor_ver == MBEDTLS_SSL_MINOR_VERSION_3 )
    {
        size_t sig_alg_len = ( ( buf[mbedtls_ssl_hs_hdr_len( ssl ) + 1 + n] <<  8 )
                             | ( buf[mbedtls_ssl_hs_hdr_len( ssl ) + 2 + n]       ) );
#if defined(MBEDTLS_DEBUG_C)
        unsigned char* sig_alg = buf + mbedtls_ssl_hs_hdr_len( ssl ) + 3 + n;
        size_t i;

        for( i = 0; i < sig_alg_len; i += 2 )
        {
            MBEDTLS_SSL_DEBUG_MSG( 3, ( "Supported Signature Algorithm found: %d"
                                        ",%d", sig_alg[i], sig_alg[i + 1]  ) );
        }
#endif

        n += 2 + sig_alg_len;

        if( ssl->in_hslen < mbedtls_ssl_hs_hdr_len( ssl ) + 2 + n )
        {
            MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate request message" ) );
            mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                            MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
            return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST );
        }
    }
#endif /* MBEDTLS_SSL_PROTO_TLS1_2 */

    /* certificate_authorities */
    dn_len = ( ( buf[mbedtls_ssl_hs_hdr_len( ssl ) + 1 + n] <<  8 )
             | ( buf[mbedtls_ssl_hs_hdr_len( ssl ) + 2 + n]       ) );

    n += dn_len;
    if( ssl->in_hslen != mbedtls_ssl_hs_hdr_len( ssl ) + 3 + n )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "bad certificate request message" ) );
        mbedtls_ssl_send_alert_message( ssl, MBEDTLS_SSL_ALERT_LEVEL_FATAL,
                                        MBEDTLS_SSL_ALERT_MSG_DECODE_ERROR );
        return( MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST );
    }

exit:
    MBEDTLS_SSL_DEBUG_MSG( 2, ( "<= parse certificate request" ) );

    return( 0 );
}
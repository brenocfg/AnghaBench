#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mbedtls_x509_crt ;
struct TYPE_3__ {int key_exchange; } ;
typedef  TYPE_1__ mbedtls_ssl_ciphersuite_t ;

/* Variables and functions */
#define  MBEDTLS_KEY_EXCHANGE_DHE_PSK 139 
#define  MBEDTLS_KEY_EXCHANGE_DHE_RSA 138 
#define  MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA 137 
#define  MBEDTLS_KEY_EXCHANGE_ECDHE_PSK 136 
#define  MBEDTLS_KEY_EXCHANGE_ECDHE_RSA 135 
#define  MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA 134 
#define  MBEDTLS_KEY_EXCHANGE_ECDH_RSA 133 
#define  MBEDTLS_KEY_EXCHANGE_ECJPAKE 132 
#define  MBEDTLS_KEY_EXCHANGE_NONE 131 
#define  MBEDTLS_KEY_EXCHANGE_PSK 130 
#define  MBEDTLS_KEY_EXCHANGE_RSA 129 
#define  MBEDTLS_KEY_EXCHANGE_RSA_PSK 128 
 char* MBEDTLS_OID_CLIENT_AUTH ; 
 char* MBEDTLS_OID_SERVER_AUTH ; 
 size_t MBEDTLS_OID_SIZE (char*) ; 
 int MBEDTLS_SSL_IS_SERVER ; 
 int /*<<< orphan*/  MBEDTLS_X509_BADCERT_EXT_KEY_USAGE ; 
 int /*<<< orphan*/  MBEDTLS_X509_BADCERT_KEY_USAGE ; 
 int MBEDTLS_X509_KU_DIGITAL_SIGNATURE ; 
 int MBEDTLS_X509_KU_KEY_AGREEMENT ; 
 int MBEDTLS_X509_KU_KEY_ENCIPHERMENT ; 
 scalar_t__ mbedtls_x509_crt_check_extended_key_usage (int /*<<< orphan*/  const*,char const*,size_t) ; 
 scalar_t__ mbedtls_x509_crt_check_key_usage (int /*<<< orphan*/  const*,int) ; 

int mbedtls_ssl_check_cert_usage( const mbedtls_x509_crt *cert,
                          const mbedtls_ssl_ciphersuite_t *ciphersuite,
                          int cert_endpoint,
                          uint32_t *flags )
{
    int ret = 0;
#if defined(MBEDTLS_X509_CHECK_KEY_USAGE)
    int usage = 0;
#endif
#if defined(MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE)
    const char *ext_oid;
    size_t ext_len;
#endif

#if !defined(MBEDTLS_X509_CHECK_KEY_USAGE) &&          \
    !defined(MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE)
    ((void) cert);
    ((void) cert_endpoint);
    ((void) flags);
#endif

#if defined(MBEDTLS_X509_CHECK_KEY_USAGE)
    if( cert_endpoint == MBEDTLS_SSL_IS_SERVER )
    {
        /* Server part of the key exchange */
        switch( ciphersuite->key_exchange )
        {
            case MBEDTLS_KEY_EXCHANGE_RSA:
            case MBEDTLS_KEY_EXCHANGE_RSA_PSK:
                usage = MBEDTLS_X509_KU_KEY_ENCIPHERMENT;
                break;

            case MBEDTLS_KEY_EXCHANGE_DHE_RSA:
            case MBEDTLS_KEY_EXCHANGE_ECDHE_RSA:
            case MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA:
                usage = MBEDTLS_X509_KU_DIGITAL_SIGNATURE;
                break;

            case MBEDTLS_KEY_EXCHANGE_ECDH_RSA:
            case MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA:
                usage = MBEDTLS_X509_KU_KEY_AGREEMENT;
                break;

            /* Don't use default: we want warnings when adding new values */
            case MBEDTLS_KEY_EXCHANGE_NONE:
            case MBEDTLS_KEY_EXCHANGE_PSK:
            case MBEDTLS_KEY_EXCHANGE_DHE_PSK:
            case MBEDTLS_KEY_EXCHANGE_ECDHE_PSK:
            case MBEDTLS_KEY_EXCHANGE_ECJPAKE:
                usage = 0;
        }
    }
    else
    {
        /* Client auth: we only implement rsa_sign and mbedtls_ecdsa_sign for now */
        usage = MBEDTLS_X509_KU_DIGITAL_SIGNATURE;
    }

    if( mbedtls_x509_crt_check_key_usage( cert, usage ) != 0 )
    {
        *flags |= MBEDTLS_X509_BADCERT_KEY_USAGE;
        ret = -1;
    }
#else
    ((void) ciphersuite);
#endif /* MBEDTLS_X509_CHECK_KEY_USAGE */

#if defined(MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE)
    if( cert_endpoint == MBEDTLS_SSL_IS_SERVER )
    {
        ext_oid = MBEDTLS_OID_SERVER_AUTH;
        ext_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_SERVER_AUTH );
    }
    else
    {
        ext_oid = MBEDTLS_OID_CLIENT_AUTH;
        ext_len = MBEDTLS_OID_SIZE( MBEDTLS_OID_CLIENT_AUTH );
    }

    if( mbedtls_x509_crt_check_extended_key_usage( cert, ext_oid, ext_len ) != 0 )
    {
        *flags |= MBEDTLS_X509_BADCERT_EXT_KEY_USAGE;
        ret = -1;
    }
#endif /* MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE */

    return( ret );
}
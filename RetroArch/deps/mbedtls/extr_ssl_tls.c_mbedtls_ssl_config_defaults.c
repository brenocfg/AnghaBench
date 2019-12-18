#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t min_minor_ver; int dhm_min_bitlen; int /*<<< orphan*/  curve_list; int /*<<< orphan*/  sig_hashes; int /*<<< orphan*/ * cert_profile; int /*<<< orphan*/ * ciphersuite_list; void* max_minor_ver; void* max_major_ver; void* min_major_ver; scalar_t__ renego_period; int /*<<< orphan*/  renego_max_records; int /*<<< orphan*/  hs_timeout_max; int /*<<< orphan*/  hs_timeout_min; int /*<<< orphan*/  cert_req_ca_list; int /*<<< orphan*/  anti_replay; int /*<<< orphan*/  f_cookie_check; int /*<<< orphan*/  f_cookie_write; int /*<<< orphan*/  cbc_record_splitting; int /*<<< orphan*/  extended_ms; int /*<<< orphan*/  encrypt_then_mac; int /*<<< orphan*/  arc4_disabled; int /*<<< orphan*/  session_tickets; int /*<<< orphan*/  authmode; } ;
typedef  TYPE_1__ mbedtls_ssl_config ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_DHM_RFC5114_MODP_2048_G ; 
 int /*<<< orphan*/  MBEDTLS_DHM_RFC5114_MODP_2048_P ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ANTI_REPLAY_ENABLED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ARC4_DISABLED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_CBC_RECORD_SPLITTING_ENABLED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_CERT_REQ_CA_LIST_ENABLED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DTLS_TIMEOUT_DFL_MAX ; 
 int /*<<< orphan*/  MBEDTLS_SSL_DTLS_TIMEOUT_DFL_MIN ; 
 int /*<<< orphan*/  MBEDTLS_SSL_ETM_ENABLED ; 
 int /*<<< orphan*/  MBEDTLS_SSL_EXTENDED_MS_ENABLED ; 
 int MBEDTLS_SSL_IS_CLIENT ; 
 int MBEDTLS_SSL_IS_SERVER ; 
 void* MBEDTLS_SSL_MAJOR_VERSION_3 ; 
 void* MBEDTLS_SSL_MAX_MAJOR_VERSION ; 
 void* MBEDTLS_SSL_MAX_MINOR_VERSION ; 
 size_t MBEDTLS_SSL_MINOR_VERSION_0 ; 
 size_t MBEDTLS_SSL_MINOR_VERSION_1 ; 
 size_t MBEDTLS_SSL_MINOR_VERSION_2 ; 
 size_t MBEDTLS_SSL_MINOR_VERSION_3 ; 
#define  MBEDTLS_SSL_PRESET_SUITEB 128 
 int /*<<< orphan*/  MBEDTLS_SSL_RENEGO_MAX_RECORDS_DEFAULT ; 
 int /*<<< orphan*/  MBEDTLS_SSL_SESSION_TICKETS_ENABLED ; 
 int MBEDTLS_SSL_TRANSPORT_DATAGRAM ; 
 int /*<<< orphan*/  MBEDTLS_SSL_VERIFY_REQUIRED ; 
 int /*<<< orphan*/  mbedtls_ecp_grp_id_list () ; 
 int mbedtls_ssl_conf_dh_param (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_endpoint (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_transport (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mbedtls_ssl_list_ciphersuites () ; 
 int /*<<< orphan*/  mbedtls_x509_crt_profile_default ; 
 int /*<<< orphan*/  mbedtls_x509_crt_profile_suiteb ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 
 int /*<<< orphan*/  ssl_cookie_check_dummy ; 
 int /*<<< orphan*/  ssl_cookie_write_dummy ; 
 int /*<<< orphan*/  ssl_preset_default_hashes ; 
 int /*<<< orphan*/  ssl_preset_suiteb_ciphersuites ; 
 int /*<<< orphan*/  ssl_preset_suiteb_curves ; 
 int /*<<< orphan*/  ssl_preset_suiteb_hashes ; 

int mbedtls_ssl_config_defaults( mbedtls_ssl_config *conf,
                                 int endpoint, int transport, int preset )
{
#if defined(MBEDTLS_DHM_C) && defined(MBEDTLS_SSL_SRV_C)
    int ret;
#endif

    /* Use the functions here so that they are covered in tests,
     * but otherwise access member directly for efficiency */
    mbedtls_ssl_conf_endpoint( conf, endpoint );
    mbedtls_ssl_conf_transport( conf, transport );

    /*
     * Things that are common to all presets
     */
#if defined(MBEDTLS_SSL_CLI_C)
    if( endpoint == MBEDTLS_SSL_IS_CLIENT )
    {
        conf->authmode = MBEDTLS_SSL_VERIFY_REQUIRED;
#if defined(MBEDTLS_SSL_SESSION_TICKETS)
        conf->session_tickets = MBEDTLS_SSL_SESSION_TICKETS_ENABLED;
#endif
    }
#endif

#if defined(MBEDTLS_ARC4_C)
    conf->arc4_disabled = MBEDTLS_SSL_ARC4_DISABLED;
#endif

#if defined(MBEDTLS_SSL_ENCRYPT_THEN_MAC)
    conf->encrypt_then_mac = MBEDTLS_SSL_ETM_ENABLED;
#endif

#if defined(MBEDTLS_SSL_EXTENDED_MASTER_SECRET)
    conf->extended_ms = MBEDTLS_SSL_EXTENDED_MS_ENABLED;
#endif

#if defined(MBEDTLS_SSL_CBC_RECORD_SPLITTING)
    conf->cbc_record_splitting = MBEDTLS_SSL_CBC_RECORD_SPLITTING_ENABLED;
#endif

#if defined(MBEDTLS_SSL_DTLS_HELLO_VERIFY) && defined(MBEDTLS_SSL_SRV_C)
    conf->f_cookie_write = ssl_cookie_write_dummy;
    conf->f_cookie_check = ssl_cookie_check_dummy;
#endif

#if defined(MBEDTLS_SSL_DTLS_ANTI_REPLAY)
    conf->anti_replay = MBEDTLS_SSL_ANTI_REPLAY_ENABLED;
#endif

#if defined(MBEDTLS_SSL_SRV_C)
    conf->cert_req_ca_list = MBEDTLS_SSL_CERT_REQ_CA_LIST_ENABLED;
#endif

#if defined(MBEDTLS_SSL_PROTO_DTLS)
    conf->hs_timeout_min = MBEDTLS_SSL_DTLS_TIMEOUT_DFL_MIN;
    conf->hs_timeout_max = MBEDTLS_SSL_DTLS_TIMEOUT_DFL_MAX;
#endif

#if defined(MBEDTLS_SSL_RENEGOTIATION)
    conf->renego_max_records = MBEDTLS_SSL_RENEGO_MAX_RECORDS_DEFAULT;
    memset( conf->renego_period,     0x00, 2 );
    memset( conf->renego_period + 2, 0xFF, 6 );
#endif

#if defined(MBEDTLS_DHM_C) && defined(MBEDTLS_SSL_SRV_C)
            if( endpoint == MBEDTLS_SSL_IS_SERVER )
            {
                if( ( ret = mbedtls_ssl_conf_dh_param( conf,
                                MBEDTLS_DHM_RFC5114_MODP_2048_P,
                                MBEDTLS_DHM_RFC5114_MODP_2048_G ) ) != 0 )
                {
                    return( ret );
                }
            }
#endif

    /*
     * Preset-specific defaults
     */
    switch( preset )
    {
        /*
         * NSA Suite B
         */
        case MBEDTLS_SSL_PRESET_SUITEB:
            conf->min_major_ver = MBEDTLS_SSL_MAJOR_VERSION_3;
            conf->min_minor_ver = MBEDTLS_SSL_MINOR_VERSION_3; /* TLS 1.2 */
            conf->max_major_ver = MBEDTLS_SSL_MAX_MAJOR_VERSION;
            conf->max_minor_ver = MBEDTLS_SSL_MAX_MINOR_VERSION;

            conf->ciphersuite_list[MBEDTLS_SSL_MINOR_VERSION_0] =
            conf->ciphersuite_list[MBEDTLS_SSL_MINOR_VERSION_1] =
            conf->ciphersuite_list[MBEDTLS_SSL_MINOR_VERSION_2] =
            conf->ciphersuite_list[MBEDTLS_SSL_MINOR_VERSION_3] =
                                   ssl_preset_suiteb_ciphersuites;

#if defined(MBEDTLS_X509_CRT_PARSE_C)
            conf->cert_profile = &mbedtls_x509_crt_profile_suiteb;
#endif

#if defined(MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
            conf->sig_hashes = ssl_preset_suiteb_hashes;
#endif

#if defined(MBEDTLS_ECP_C)
            conf->curve_list = ssl_preset_suiteb_curves;
#endif
            break;

        /*
         * Default
         */
        default:
            conf->min_major_ver = MBEDTLS_SSL_MAJOR_VERSION_3;
            conf->min_minor_ver = MBEDTLS_SSL_MINOR_VERSION_1; /* TLS 1.0 */
            conf->max_major_ver = MBEDTLS_SSL_MAX_MAJOR_VERSION;
            conf->max_minor_ver = MBEDTLS_SSL_MAX_MINOR_VERSION;

#if defined(MBEDTLS_SSL_PROTO_DTLS)
            if( transport == MBEDTLS_SSL_TRANSPORT_DATAGRAM )
                conf->min_minor_ver = MBEDTLS_SSL_MINOR_VERSION_2;
#endif

            conf->ciphersuite_list[MBEDTLS_SSL_MINOR_VERSION_0] =
            conf->ciphersuite_list[MBEDTLS_SSL_MINOR_VERSION_1] =
            conf->ciphersuite_list[MBEDTLS_SSL_MINOR_VERSION_2] =
            conf->ciphersuite_list[MBEDTLS_SSL_MINOR_VERSION_3] =
                                   mbedtls_ssl_list_ciphersuites();

#if defined(MBEDTLS_X509_CRT_PARSE_C)
            conf->cert_profile = &mbedtls_x509_crt_profile_default;
#endif

#if defined(MBEDTLS_KEY_EXCHANGE__WITH_CERT__ENABLED)
            conf->sig_hashes = ssl_preset_default_hashes;
#endif

#if defined(MBEDTLS_ECP_C)
            conf->curve_list = mbedtls_ecp_grp_id_list();
#endif

#if defined(MBEDTLS_DHM_C) && defined(MBEDTLS_SSL_CLI_C)
            conf->dhm_min_bitlen = 1024;
#endif
    }

    return( 0 );
}
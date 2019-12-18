#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; } ;
struct ssl_pm {TYPE_1__ ssl; } ;
struct TYPE_5__ {scalar_t__ ssl_pm; } ;
typedef  TYPE_2__ SSL ;
typedef  int /*<<< orphan*/  OSSL_HANDSHAKE_STATE ;

/* Variables and functions */
#define  MBEDTLS_SSL_CLIENT_CERTIFICATE 141 
#define  MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC 140 
#define  MBEDTLS_SSL_CLIENT_FINISHED 139 
#define  MBEDTLS_SSL_CLIENT_HELLO 138 
#define  MBEDTLS_SSL_CLIENT_KEY_EXCHANGE 137 
#define  MBEDTLS_SSL_HANDSHAKE_OVER 136 
#define  MBEDTLS_SSL_SERVER_CERTIFICATE 135 
#define  MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC 134 
#define  MBEDTLS_SSL_SERVER_FINISHED 133 
#define  MBEDTLS_SSL_SERVER_HELLO 132 
#define  MBEDTLS_SSL_SERVER_HELLO_DONE 131 
#define  MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT 130 
#define  MBEDTLS_SSL_SERVER_KEY_EXCHANGE 129 
#define  MBEDTLS_SSL_SERVER_NEW_SESSION_TICKET 128 
 int /*<<< orphan*/  TLS_ST_BEFORE ; 
 int /*<<< orphan*/  TLS_ST_CW_CERT ; 
 int /*<<< orphan*/  TLS_ST_CW_CHANGE ; 
 int /*<<< orphan*/  TLS_ST_CW_CLNT_HELLO ; 
 int /*<<< orphan*/  TLS_ST_CW_FINISHED ; 
 int /*<<< orphan*/  TLS_ST_CW_KEY_EXCH ; 
 int /*<<< orphan*/  TLS_ST_OK ; 
 int /*<<< orphan*/  TLS_ST_SR_KEY_EXCH ; 
 int /*<<< orphan*/  TLS_ST_SW_CERT ; 
 int /*<<< orphan*/  TLS_ST_SW_CERT_REQ ; 
 int /*<<< orphan*/  TLS_ST_SW_CHANGE ; 
 int /*<<< orphan*/  TLS_ST_SW_FINISHED ; 
 int /*<<< orphan*/  TLS_ST_SW_SESSION_TICKET ; 
 int /*<<< orphan*/  TLS_ST_SW_SRVR_DONE ; 
 int /*<<< orphan*/  TLS_ST_SW_SRVR_HELLO ; 

OSSL_HANDSHAKE_STATE ssl_pm_get_state(const SSL *ssl)
{
    OSSL_HANDSHAKE_STATE state;

    struct ssl_pm *ssl_pm = (struct ssl_pm *)ssl->ssl_pm;

    switch (ssl_pm->ssl.state)
    {
        case MBEDTLS_SSL_CLIENT_HELLO:
            state = TLS_ST_CW_CLNT_HELLO;
            break;
        case MBEDTLS_SSL_SERVER_HELLO:
            state = TLS_ST_SW_SRVR_HELLO;
            break;
        case MBEDTLS_SSL_SERVER_CERTIFICATE:
            state = TLS_ST_SW_CERT;
            break;
        case MBEDTLS_SSL_SERVER_HELLO_DONE:
            state = TLS_ST_SW_SRVR_DONE;
            break;
        case MBEDTLS_SSL_CLIENT_KEY_EXCHANGE:
            state = TLS_ST_CW_KEY_EXCH;
            break;
        case MBEDTLS_SSL_CLIENT_CHANGE_CIPHER_SPEC:
            state = TLS_ST_CW_CHANGE;
            break;
        case MBEDTLS_SSL_CLIENT_FINISHED:
            state = TLS_ST_CW_FINISHED;
            break;
        case MBEDTLS_SSL_SERVER_CHANGE_CIPHER_SPEC:
            state = TLS_ST_SW_CHANGE;
            break;
        case MBEDTLS_SSL_SERVER_FINISHED:
            state = TLS_ST_SW_FINISHED;
            break;
        case MBEDTLS_SSL_CLIENT_CERTIFICATE:
            state = TLS_ST_CW_CERT;
            break;
        case MBEDTLS_SSL_SERVER_KEY_EXCHANGE:
            state = TLS_ST_SR_KEY_EXCH;
            break;
        case MBEDTLS_SSL_SERVER_NEW_SESSION_TICKET:
            state = TLS_ST_SW_SESSION_TICKET;
            break;
        case MBEDTLS_SSL_SERVER_HELLO_VERIFY_REQUEST_SENT:
            state = TLS_ST_SW_CERT_REQ;
            break;
        case MBEDTLS_SSL_HANDSHAKE_OVER:
            state = TLS_ST_OK;
            break;
        default :
            state = TLS_ST_BEFORE;
            break;
    }

    return state;
}
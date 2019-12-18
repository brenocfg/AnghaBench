#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
#define  DTLS_ST_CR_HELLO_VERIFY_REQUEST 160 
#define  DTLS_ST_SW_HELLO_VERIFY_REQUEST 159 
 int /*<<< orphan*/  SSL_ASSERT2 (int /*<<< orphan*/  const*) ; 
 int SSL_get_state (int /*<<< orphan*/  const*) ; 
#define  TLS_ST_BEFORE 158 
#define  TLS_ST_CR_CERT 157 
#define  TLS_ST_CR_CERT_REQ 156 
#define  TLS_ST_CR_CHANGE 155 
#define  TLS_ST_CR_FINISHED 154 
#define  TLS_ST_CR_KEY_EXCH 153 
#define  TLS_ST_CR_SESSION_TICKET 152 
#define  TLS_ST_CR_SRVR_DONE 151 
#define  TLS_ST_CR_SRVR_HELLO 150 
#define  TLS_ST_CW_CERT 149 
#define  TLS_ST_CW_CERT_VRFY 148 
#define  TLS_ST_CW_CHANGE 147 
#define  TLS_ST_CW_CLNT_HELLO 146 
#define  TLS_ST_CW_FINISHED 145 
#define  TLS_ST_CW_KEY_EXCH 144 
#define  TLS_ST_OK 143 
#define  TLS_ST_SR_CERT 142 
#define  TLS_ST_SR_CERT_VRFY 141 
#define  TLS_ST_SR_CHANGE 140 
#define  TLS_ST_SR_CLNT_HELLO 139 
#define  TLS_ST_SR_FINISHED 138 
#define  TLS_ST_SR_KEY_EXCH 137 
#define  TLS_ST_SW_CERT 136 
#define  TLS_ST_SW_CERT_REQ 135 
#define  TLS_ST_SW_CHANGE 134 
#define  TLS_ST_SW_FINISHED 133 
#define  TLS_ST_SW_HELLO_REQ 132 
#define  TLS_ST_SW_KEY_EXCH 131 
#define  TLS_ST_SW_SESSION_TICKET 130 
#define  TLS_ST_SW_SRVR_DONE 129 
#define  TLS_ST_SW_SRVR_HELLO 128 
 scalar_t__ ossl_statem_in_error (int /*<<< orphan*/  const*) ; 

const char *SSL_state_string_long(const SSL *ssl)
{
    const char *str = "UNKWN ";

    SSL_ASSERT2(ssl);

    if (ossl_statem_in_error(ssl))
        str = "SSLERR";
    else
    {
        switch (SSL_get_state(ssl))
        {
            case TLS_ST_BEFORE:
                str = "before SSL initialization";
                break;
            case TLS_ST_OK:
                str = "SSL negotiation finished successfully";
                break;
            case TLS_ST_CW_CLNT_HELLO:
                str = "SSLv3/TLS write client hello";
                break;
            case TLS_ST_CR_SRVR_HELLO:
                str = "SSLv3/TLS read server hello";
                break;
            case TLS_ST_CR_CERT:
                str = "SSLv3/TLS read server certificate";
                break;
            case TLS_ST_CR_KEY_EXCH:
                str = "SSLv3/TLS read server key exchange";
                break;
            case TLS_ST_CR_CERT_REQ:
                str = "SSLv3/TLS read server certificate request";
                break;
            case TLS_ST_CR_SESSION_TICKET:
                str = "SSLv3/TLS read server session ticket";
                break;
            case TLS_ST_CR_SRVR_DONE:
                str = "SSLv3/TLS read server done";
                break;
            case TLS_ST_CW_CERT:
                str = "SSLv3/TLS write client certificate";
                break;
            case TLS_ST_CW_KEY_EXCH:
                str = "SSLv3/TLS write client key exchange";
                break;
            case TLS_ST_CW_CERT_VRFY:
                str = "SSLv3/TLS write certificate verify";
                break;
            case TLS_ST_CW_CHANGE:
            case TLS_ST_SW_CHANGE:
                str = "SSLv3/TLS write change cipher spec";
                break;
            case TLS_ST_CW_FINISHED:
            case TLS_ST_SW_FINISHED:
                str = "SSLv3/TLS write finished";
                break;
            case TLS_ST_CR_CHANGE:
            case TLS_ST_SR_CHANGE:
                str = "SSLv3/TLS read change cipher spec";
                break;
            case TLS_ST_CR_FINISHED:
            case TLS_ST_SR_FINISHED:
                str = "SSLv3/TLS read finished";
                break;
            case TLS_ST_SR_CLNT_HELLO:
                str = "SSLv3/TLS read client hello";
                break;
            case TLS_ST_SW_HELLO_REQ:
                str = "SSLv3/TLS write hello request";
                break;
            case TLS_ST_SW_SRVR_HELLO:
                str = "SSLv3/TLS write server hello";
                break;
            case TLS_ST_SW_CERT:
                str = "SSLv3/TLS write certificate";
                break;
            case TLS_ST_SW_KEY_EXCH:
                str = "SSLv3/TLS write key exchange";
                break;
            case TLS_ST_SW_CERT_REQ:
                str = "SSLv3/TLS write certificate request";
                break;
            case TLS_ST_SW_SESSION_TICKET:
                str = "SSLv3/TLS write session ticket";
                break;
            case TLS_ST_SW_SRVR_DONE:
                str = "SSLv3/TLS write server done";
                break;
            case TLS_ST_SR_CERT:
                str = "SSLv3/TLS read client certificate";
                break;
            case TLS_ST_SR_KEY_EXCH:
                str = "SSLv3/TLS read client key exchange";
                break;
            case TLS_ST_SR_CERT_VRFY:
                str = "SSLv3/TLS read certificate verify";
                break;
            case DTLS_ST_CR_HELLO_VERIFY_REQUEST:
                str = "DTLS1 read hello verify request";
                break;
            case DTLS_ST_SW_HELLO_VERIFY_REQUEST:
                str = "DTLS1 write hello verify request";
                break;
            default:
                break;
        }
    }

    return str;
}
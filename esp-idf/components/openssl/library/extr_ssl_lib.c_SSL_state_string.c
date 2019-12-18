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
#define  DTLS_ST_CR_HELLO_VERIFY_REQUEST 158 
#define  DTLS_ST_SW_HELLO_VERIFY_REQUEST 157 
 int /*<<< orphan*/  SSL_ASSERT2 (int /*<<< orphan*/  const*) ; 
 int SSL_get_state (int /*<<< orphan*/  const*) ; 
#define  TLS_ST_BEFORE 156 
#define  TLS_ST_CR_CERT 155 
#define  TLS_ST_CR_CERT_REQ 154 
#define  TLS_ST_CR_CHANGE 153 
#define  TLS_ST_CR_FINISHED 152 
#define  TLS_ST_CR_KEY_EXCH 151 
#define  TLS_ST_CR_SRVR_DONE 150 
#define  TLS_ST_CR_SRVR_HELLO 149 
#define  TLS_ST_CW_CERT 148 
#define  TLS_ST_CW_CERT_VRFY 147 
#define  TLS_ST_CW_CHANGE 146 
#define  TLS_ST_CW_CLNT_HELLO 145 
#define  TLS_ST_CW_FINISHED 144 
#define  TLS_ST_CW_KEY_EXCH 143 
#define  TLS_ST_OK 142 
#define  TLS_ST_SR_CERT 141 
#define  TLS_ST_SR_CERT_VRFY 140 
#define  TLS_ST_SR_CHANGE 139 
#define  TLS_ST_SR_CLNT_HELLO 138 
#define  TLS_ST_SR_FINISHED 137 
#define  TLS_ST_SR_KEY_EXCH 136 
#define  TLS_ST_SW_CERT 135 
#define  TLS_ST_SW_CERT_REQ 134 
#define  TLS_ST_SW_CHANGE 133 
#define  TLS_ST_SW_FINISHED 132 
#define  TLS_ST_SW_HELLO_REQ 131 
#define  TLS_ST_SW_KEY_EXCH 130 
#define  TLS_ST_SW_SRVR_DONE 129 
#define  TLS_ST_SW_SRVR_HELLO 128 
 scalar_t__ ossl_statem_in_error (int /*<<< orphan*/  const*) ; 

const char *SSL_state_string(const SSL *ssl)
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
                str = "PINIT ";
                break;
            case TLS_ST_OK:
                str =  "SSLOK ";
                break;
            case TLS_ST_CW_CLNT_HELLO:
                str = "TWCH";
                break;
            case TLS_ST_CR_SRVR_HELLO:
                str = "TRSH";
                break;
            case TLS_ST_CR_CERT:
                str = "TRSC";
                break;
            case TLS_ST_CR_KEY_EXCH:
                str = "TRSKE";
                break;
            case TLS_ST_CR_CERT_REQ:
                str = "TRCR";
                break;
            case TLS_ST_CR_SRVR_DONE:
                str = "TRSD";
                break;
            case TLS_ST_CW_CERT:
                str = "TWCC";
                break;
            case TLS_ST_CW_KEY_EXCH:
                str = "TWCKE";
                break;
            case TLS_ST_CW_CERT_VRFY:
                str = "TWCV";
                break;
            case TLS_ST_SW_CHANGE:
            case TLS_ST_CW_CHANGE:
                str = "TWCCS";
                break;
            case TLS_ST_SW_FINISHED:
            case TLS_ST_CW_FINISHED:
                str = "TWFIN";
                break;
            case TLS_ST_SR_CHANGE:
            case TLS_ST_CR_CHANGE:
                str = "TRCCS";
                break;
            case TLS_ST_SR_FINISHED:
            case TLS_ST_CR_FINISHED:
                str = "TRFIN";
                break;
            case TLS_ST_SW_HELLO_REQ:
                str = "TWHR";
                break;
            case TLS_ST_SR_CLNT_HELLO:
                str = "TRCH";
                break;
            case TLS_ST_SW_SRVR_HELLO:
                str = "TWSH";
                break;
            case TLS_ST_SW_CERT:
                str = "TWSC";
                break;
            case TLS_ST_SW_KEY_EXCH:
                str = "TWSKE";
                break;
            case TLS_ST_SW_CERT_REQ:
                str = "TWCR";
                break;
            case TLS_ST_SW_SRVR_DONE:
                str = "TWSD";
                break;
            case TLS_ST_SR_CERT:
                str = "TRCC";
                break;
            case TLS_ST_SR_KEY_EXCH:
                str = "TRCKE";
                break;
            case TLS_ST_SR_CERT_VRFY:
                str = "TRCV";
                break;
            case DTLS_ST_CR_HELLO_VERIFY_REQUEST:
                str = "DRCHV";
                break;
            case DTLS_ST_SW_HELLO_VERIFY_REQUEST:
                str = "DWCHV";
                break;
            default:
                break;
        }
    }

    return str;
}
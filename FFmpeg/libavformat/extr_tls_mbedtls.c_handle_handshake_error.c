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
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  MBEDTLS_ERR_NET_CONN_RESET 131 
#define  MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED 130 
#define  MBEDTLS_ERR_SSL_FATAL_ALERT_MESSAGE 129 
#define  MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void handle_handshake_error(URLContext *h, int ret)
{
    switch (ret) {
    case MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE:
        av_log(h, AV_LOG_ERROR, "None of the common ciphersuites is usable. Was the local certificate correctly set?\n");
        break;
    case MBEDTLS_ERR_SSL_FATAL_ALERT_MESSAGE:
        av_log(h, AV_LOG_ERROR, "A fatal alert message was received from the peer, has the peer a correct certificate?\n");
        break;
    case MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED:
        av_log(h, AV_LOG_ERROR, "No CA chain is set, but required to operate. Was the CA correctly set?\n");
        break;
    case MBEDTLS_ERR_NET_CONN_RESET:
        av_log(h, AV_LOG_ERROR, "TLS handshake was aborted by peer.\n");
        break;
    default:
        av_log(h, AV_LOG_ERROR, "mbedtls_ssl_handshake returned -0x%x\n", -ret);
        break;
    }
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct x509_pm {scalar_t__ ex_crt; scalar_t__ x509_crt; } ;
struct ssl_pm {int /*<<< orphan*/  conf; } ;
struct pkey_pm {scalar_t__ ex_pkey; scalar_t__ pkey; } ;
struct TYPE_11__ {int verify_mode; TYPE_4__* cert; TYPE_1__* client_CA; struct ssl_pm* ssl_pm; } ;
struct TYPE_10__ {TYPE_3__* x509; TYPE_2__* pkey; } ;
struct TYPE_9__ {scalar_t__ x509_pm; } ;
struct TYPE_8__ {scalar_t__ pkey_pm; } ;
struct TYPE_7__ {scalar_t__ x509_pm; } ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 int MBEDTLS_SSL_VERIFY_NONE ; 
 int MBEDTLS_SSL_VERIFY_OPTIONAL ; 
 int MBEDTLS_SSL_VERIFY_REQUIRED ; 
 int MBEDTLS_SSL_VERIFY_UNSET ; 
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SSL_PLATFORM_ERROR_LEVEL ; 
 int SSL_VERIFY_CLIENT_ONCE ; 
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_authmode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mbedtls_ssl_conf_ca_chain (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int mbedtls_ssl_conf_own_cert (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ssl_pm_reload_crt(SSL *ssl)
{
    int ret;
    int mode;
    struct ssl_pm *ssl_pm = ssl->ssl_pm;
    struct x509_pm *ca_pm = (struct x509_pm *)ssl->client_CA->x509_pm;

    struct pkey_pm *pkey_pm = (struct pkey_pm *)ssl->cert->pkey->pkey_pm;
    struct x509_pm *crt_pm = (struct x509_pm *)ssl->cert->x509->x509_pm;

    if (ssl->verify_mode & SSL_VERIFY_FAIL_IF_NO_PEER_CERT)
        mode = MBEDTLS_SSL_VERIFY_REQUIRED;
    else if (ssl->verify_mode & SSL_VERIFY_PEER)
        mode = MBEDTLS_SSL_VERIFY_OPTIONAL;
    else if (ssl->verify_mode & SSL_VERIFY_CLIENT_ONCE)
        mode = MBEDTLS_SSL_VERIFY_UNSET;
    else
        mode = MBEDTLS_SSL_VERIFY_NONE;

    mbedtls_ssl_conf_authmode(&ssl_pm->conf, mode);

    if (ca_pm->x509_crt) {
        mbedtls_ssl_conf_ca_chain(&ssl_pm->conf, ca_pm->x509_crt, NULL);
    } else if (ca_pm->ex_crt) {
        mbedtls_ssl_conf_ca_chain(&ssl_pm->conf, ca_pm->ex_crt, NULL);
    }

    if (crt_pm->x509_crt && pkey_pm->pkey) {
        ret = mbedtls_ssl_conf_own_cert(&ssl_pm->conf, crt_pm->x509_crt, pkey_pm->pkey);
    } else if (crt_pm->ex_crt && pkey_pm->ex_pkey) {
        ret = mbedtls_ssl_conf_own_cert(&ssl_pm->conf, crt_pm->ex_crt, pkey_pm->ex_pkey);
    } else {
        ret = 0;
    }

    if (ret) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_ssl_conf_own_cert() return -0x%x", -ret);
        ret = -1;
    }

    return ret;
}
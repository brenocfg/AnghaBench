#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct x509_pm {int /*<<< orphan*/ * ex_crt; } ;
struct ssl_pm {int /*<<< orphan*/  ssl; } ;
struct TYPE_7__ {TYPE_2__* session; scalar_t__ ssl_pm; } ;
struct TYPE_6__ {TYPE_1__* peer; } ;
struct TYPE_5__ {scalar_t__ x509_pm; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SSL_PLATFORM_ERROR_LEVEL ; 
 int mbedtls_ssl_close_notify (int /*<<< orphan*/ *) ; 

int ssl_pm_shutdown(SSL *ssl)
{
    int ret;
    struct ssl_pm *ssl_pm = (struct ssl_pm *)ssl->ssl_pm;

    ret = mbedtls_ssl_close_notify(&ssl_pm->ssl);
    if (ret) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "mbedtls_ssl_close_notify() return -0x%x", -ret);
        ret = -1;
    } else {
        struct x509_pm *x509_pm = (struct x509_pm *)ssl->session->peer->x509_pm;

        x509_pm->ex_crt = NULL;
    }

    return ret;
}
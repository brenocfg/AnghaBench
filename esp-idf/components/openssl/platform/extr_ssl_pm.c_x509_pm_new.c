#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct x509_pm {int /*<<< orphan*/  x509_crt; int /*<<< orphan*/  ex_crt; } ;
struct TYPE_4__ {struct x509_pm* x509_pm; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SSL_PLATFORM_ERROR_LEVEL ; 
 struct x509_pm* ssl_mem_zalloc (int) ; 

int x509_pm_new(X509 *x, X509 *m_x)
{
    struct x509_pm *x509_pm;

    x509_pm = ssl_mem_zalloc(sizeof(struct x509_pm));
    if (!x509_pm) {
        SSL_DEBUG(SSL_PLATFORM_ERROR_LEVEL, "no enough memory > (x509_pm)");
        goto failed1;
    }

    x->x509_pm = x509_pm;

    if (m_x) {
        struct x509_pm *m_x509_pm = (struct x509_pm *)m_x->x509_pm;

        x509_pm->ex_crt = m_x509_pm->x509_crt;
    }

    return 0;

failed1:
    return -1;
}
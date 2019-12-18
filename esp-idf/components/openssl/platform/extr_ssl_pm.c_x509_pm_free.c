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
struct x509_pm {int /*<<< orphan*/ * x509_crt; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x509_pm; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int /*<<< orphan*/  mbedtls_x509_crt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_mem_free (int /*<<< orphan*/ *) ; 

void x509_pm_free(X509 *x)
{
    struct x509_pm *x509_pm = (struct x509_pm *)x->x509_pm;

    if (x509_pm->x509_crt) {
        mbedtls_x509_crt_free(x509_pm->x509_crt);

        ssl_mem_free(x509_pm->x509_crt);
        x509_pm->x509_crt = NULL;
    }

    ssl_mem_free(x->x509_pm);
    x->x509_pm = NULL;
}